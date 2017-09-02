/*	EP1 - MAC0422 
	Shell + Gerenciados de processos
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//current dir
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <grp.h>
#include <time.h>

#include <pthread.h>
#include <assert.h>
#include <semaphore.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
  char **text;
  int qnt;
} input;

/* Receive a struct input and a readline 'in',
   split the 'in' and save in the input table
   of words, couting this. */

void mysplit(char *in, input *inp) {
  int i, n = 0;
  for (i = 0; i<strlen(in) ; i++) {
    if(in[i] == 32)  {
      n++; //32 == " "
    }
  }
  inp->qnt = n+2;
  inp->text = malloc ((n+2) * sizeof(char *));
  inp->text[0] = strtok(in, " ");
  for(i = 1; i < n+1; i++) {
    inp->text[i] = strtok(NULL, " ");
  }
  inp->text[n+1] = 0; 
  return;
}

/* Receive the input, and do the external
   call, using the fork() and execve().
   Here, our implementation do any external
   call (that use fork and execve). */
void externalCalls (input inp) {
  int ret;
  ret = fork();
  if(ret == 0) {
    execv(inp.text[0], inp.text);
  }
  else if (ret == -1) {
    printf("forkFailed\n");
  }
  else {
     waitpid(ret, NULL, 0);
  }
}

/* Receive the input and execute 
   our implementation of chown function. */
void myChown (input inp) {
  int uid = getuid();
  struct group *gr;

  gr = getgrnam(inp.text[1]+1);
  chown(inp.text[2], uid, gr->gr_gid);
}

/* Receive the input and execute our implementation
   of date function using strftime funtion.
   For this :
    we include : #include <time.h>
    and use: %a %b %d %I:%M:%S %Z %Y
      for repectively day of week, month, day (decimal),
      hours, minutes, seconds, time zone and year. */
void myDate (input inp) {
  time_t t = time(NULL);
  char dateBuffer[80];
  struct tm *tm = localtime(&t);
  time(&t);
  tm = localtime(&t);

  strftime(dateBuffer,80,"%a %b %d %I:%M:%S %Z %Y", tm);
  printf("%s\n", dateBuffer);
}

/* Receive the input, verify what intern
   call should be executed, and invoke it. */
void internCalls (input inp) {
  if (strcmp(inp.text[0],"chown") == 0) {
    myChown(inp);
  }
  else if (strcmp(inp.text[0],"date") == 0) {
    myDate(inp);
  }
}

/* Receive the input, verify if the call
   required is valid in our shell and
   verify what kind of call is it, to 
   do the call (external or intern).
*/
void calls (input inp) {
  if (strcmp(inp.text[0],"/bin/ping") == 0 || strcmp(inp.text[0],"/usr/bin/cal") == 0 || strcmp(inp.text[0],"./ep1") == 0) {
    externalCalls(inp);
  }
  else if ((strcmp(inp.text[0],"chown") == 0) || (strcmp(inp.text[0],"date") == 0)) {
    internCalls(inp);
  }
  else {
    printf("Command not found\n");
  } 
}

void* perform_work( void* argument )
{

  int passed_in_value;
  pthread_mutex_lock(&mutex);
  passed_in_value = *( ( int* )argument );
  printf( "Hello World! It's me, thread with argument %d!\n", passed_in_value );
  pthread_mutex_unlock(&mutex);
 
  /* optionally: insert more useful stuff here */
  return NULL;
}

void usingThreads(int NUM_THREADS) {
  pthread_t threads[NUM_THREADS];
  int thread_args[NUM_THREADS];
  int result_code;
  unsigned index;
  //int spare;

  // create all threads one by one
  for( index = 0; index < NUM_THREADS; ++index )
  {
    thread_args[ index ] = index;
    printf("In main: creating thread %d\n", index);
    result_code = pthread_create( &threads[index], NULL, perform_work, &thread_args[index] );
    assert( !result_code );
    
  }
 
  // wait for each thread to complete
  for( index = 0; index < NUM_THREADS; ++index )
  {
    // block until thread 'index' completes
      //sem_getvalue(&mutex, &spare);
      result_code = pthread_join( threads[ index ], NULL );
      assert( !result_code );
      printf( "In main: thread %d has completed\n", index );
  }
 
  printf( "In main: All threads completed successfully\n" );
  exit( EXIT_SUCCESS );
}

int main ()
{
  using_history();
  input inp;
  char *in;
  char inPrompt[100];
  pthread_mutex_init(&mutex, NULL);
  usingThreads(5);
  pthread_mutex_destroy(&mutex);

  while(1) {
    sprintf(inPrompt, "[%s] $ ", getcwd (NULL, 1024));
    in = malloc (sizeof (char *));
    in = readline(inPrompt);
    add_history(in);
    mysplit(in, &inp);
    calls(inp);
    free(inp.text);
    free(in);
  }


  clear_history();
  return 0;
}

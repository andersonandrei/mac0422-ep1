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

/* Receive the input, verify what intern
   call should be executed, and invoke it. */
void internCalls (input inp) {
  if (strcmp(inp.text[0],"chown") == 0) {
    myChown(inp);
  }
  else if (strcmp(inp.text[0],"date") == 0) {
    date(inp);
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

int main ()
{
  using_history();
  input inp;
  char *in;
  char inPrompt[100];
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

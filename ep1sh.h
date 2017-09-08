/*	EP1 - MAC0422 
	Shell + Gerenciados de processos
*/

#ifndef EP1SH
#define EP1SH

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

//#include <ep1.c>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
  char **text;
  int qnt;
} input;

/* Receive a struct input and a readline 'in',
   split the 'in' and save in the input table
   of words, couting this. */

void mysplit(char *in, input *inp);

/* Receive the input, and do the external
   call, using the fork() and execve().
   Here, our implementation do any external
   call (that use fork and execve). */
void externalCalls (input inp);

/* Receive the input and execute 
   our implementation of chown function. */
void myChown (input inp);

/* Receive the input and execute our implementation
   of date function using strftime funtion.
   For this :
    we include : #include <time.h>
    and use: %a %b %d %I:%M:%S %Z %Y
      for repectively day of week, month, day (decimal),
      hours, minutes, seconds, time zone and year. */
void myDate (input inp);

/* Receive the input, verify what intern
   call should be executed, and invoke it. */
void internCalls (input inp);

/* Receive the input, verify if the call
   required is valid in our shell and
   verify what kind of call is it, to 
   do the call (external or intern).
*/
void calls (input inp);

void* perform_work(int i);

void usingThreads(int NUM_THREADS);


int main ();

#endif
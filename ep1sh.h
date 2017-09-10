/*	EP1 - MAC0422 
	Shell + Gerenciados de processos
*/
#ifndef EP1SH_H
#define EP1SH_H

#include "ep1.h"
#include "mainData.h"
#include "schedulerSJF.h"
#include "schedulerRoudRobin.h"
#include "schedulerPriority.h"

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
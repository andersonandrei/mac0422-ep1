/*  EP1 - MAC0422 - Anderson Andrei da Silva
    Shell + Gerenciador de processos */

#ifndef SCHEDULERROUDROBIN_H
#define SCHEDULERROUDROBIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //current dir
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <grp.h>
#include <time.h>
#define __USE_GNU
#include <sys/time.h>
#include <sys/resource.h>

#include <pthread.h>
#include <assert.h>
#include <semaphore.h>

#include <sys/queue.h>
#include "mainData.h"
#include "queue.h"
#include "ep1.h"

/* The job of the threads */
void* jobRR(void *argument);

/* Roud Robin scheduler*/
void schedulerRoudRobin(thr *process, char *name, char *output, char *d);

#endif


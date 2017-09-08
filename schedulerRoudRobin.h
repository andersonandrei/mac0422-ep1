#ifndef SCHEDULERROUDROBIN_H
#define SCHEDULERROUDROBIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //current dir
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
#include "structs.h"
#include "queue.h"
#include "ep1.h"

void enqueueThreadRR(thr thread, struct node **rearSJF, struct node **frontSJF);

void enqueueThreadsRR(thr *process, int qntProcess, struct node **rearSJF, struct node **frontSJF);

void* jobRR(void *argument);

void schedulerRoudRobin(thr *process, char *name, char *output);

#endif
#ifndef SCHEDULERSJF
#define SCHEDULERSJF

#include <time.h>
#define __USE_GNU
#include <sys/time.h>
#include <sys/resource.h>

#include <pthread.h>
#include <assert.h>
#include <semaphore.h>

#include <sys/queue.h>
#include "queue.h"

void enqueueThread(th thread);

void enqueueThreads(th *process);

void* job(void *argument);

void schedulerSJF(th *process, char *name, char *output);

#endif
#ifndef SCHEDULERSJF_H
#define SCHEDULERSJF_H

#include <time.h>
#define __USE_GNU
#include <sys/time.h>
#include <sys/resource.h>

#include <pthread.h>
#include <assert.h>
#include <semaphore.h>

#include <sys/queue.h>
#include "structs.h"

void enqueueThread(th thread);

void enqueueThreads(th *process);

void* job(void *argument);

void schedulerSJF(th *process, char *name, char *output);

#endif
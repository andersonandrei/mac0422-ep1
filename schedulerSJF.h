/*Scheduler SJF Functions */
#ifndef SCHEDULERSJF
#define SCHEDULERSJF

#include "queue.h"
#include "ep1.h"

void enqueueThread(th thread);

void enqueueThreads(th *process);

void* job(void *argument);

void schedulerSJF(th *process, char *name);

#endif

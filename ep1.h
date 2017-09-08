#ifndef EP1_H
#define EP1_H

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
#include <grp.h>

#include "schedulerSJF.h"
#include "structs.h"

#define N 1024

int qntProcess;

void printingInfo();

void createThreads(char *name);

void destroyThreads();

void executeThreads();

void enqueueThread(th thread);

void enqueueThreads(th *process);

void* job(void *argument);

void schedulerSJF(th *process, char *name, char *output);

int main(int argc, char *argv[ ]);


#endif
/*	EP1 - MAC0422 - Anderson Andrei da Silva
	Shell + Gerenciador de processos */

#ifndef EP1_H
#define EP1_H

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
#include "schedulerSJF.h"
#include "schedulerRoudRobin.h"
#include "schedulerPriority.h"
#include "mainData.h"

#define N 1024

/* Receive a FILE name, read e save the information in the process *thr */
void createThreads(char *name, int *qntProcess, int verbose);

/* Enqueu the thread ordered by dt*/
void enqueueThreadDt(thr thread, struct node **rear, struct node **front);

/* Enqueu the thread ordered by t0*/
void enqueueThreadT(thr thread, struct node **rear, struct node **front);

/* Enqueue all the threads*/
void enqueueThreads(thr *process, int qntProcess, struct node **rear, struct node **front);

int main(int argc, char *argv[ ]);


#endif
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
#include "structs.h"

#define N 1024

void printingInfo();

void createThreads(char *name, int *qntProcess);

void destroyThreads();

void executeThreads();

int main(int argc, char *argv[ ]);


#endif
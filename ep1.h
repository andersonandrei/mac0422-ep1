/* ep1 Functions */
#ifndef EP1
#define EP1

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

#define __USE_GNU
#include <sys/time.h>
#include <sys/resource.h>

#include "schedulerSJF.h"

#define N 1024

typedef struct {
	int id;
	char *name;
	float t, dt, deadline;
	pthread_t thread;
	pthread_mutex_t mutex;
} th;

th *process;
int qntProcess;

void printingInfo();

void createThreads(char *name);

void destroyThreads();

int main(int argc, char *argv[ ]);

#endif
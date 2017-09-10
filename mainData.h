#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//current dir
#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <grp.h>
#include <time.h>

#include <pthread.h>
#include <assert.h>
#include <semaphore.h>

typedef struct {
	int id;
	char *name;
	float t, dt, deadline;
	pthread_t thread;
	pthread_mutex_t mutex;
} thr;

typedef struct {
	char **text;
	int qnt;
} input;

struct node {
    int id;
    float info;
    struct node *ptr;
} *front,*rear,*temp,*front1;

#endif
#ifndef TYPES_H
#define TYPES_H

#include <pthread.h>

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
#ifndef STRUCTS_H
#define STRCUTS_H

typedef struct {
	int id;
	char *name;
	float t, dt, deadline;
	pthread_t thread;
	pthread_mutex_t mutex;
} th;
th *process;

typedef struct {
  char **text;
  int qnt;
} input;

struct node
{
    int id;
    float info;
    struct node *ptr;
} *front,*rear,*temp,*front1;

#endif
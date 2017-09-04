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

#define N 1024

typedef struct {
  pthread_t *threads;
  int *args;
  float *t;
  float *dt;
  float *deadline;
} th;

void* oi(void* argument){
	printf("Oi sou uma thread\n");
	return 0;
}


void createThreads(char *name, th process) {
  	FILE *arq;
  	int result, resultCreation;
  	int i;
  	int maxSize = N;
  	int cont = 0;
  	float t, dt, deadline;
  	char *n = malloc (1024 * sizeof(char));
  	process.threads = malloc(N * sizeof(pthread_t));
  	process.args = malloc(N * sizeof(int));
  	process.t = malloc (N * sizeof(float));
	process.dt = malloc (N * sizeof(float));
  	process.deadline = malloc (N * sizeof(float));

  	arq = fopen(name, "rt");
	if (arq != NULL) {
		result = fscanf(arq, "%f %f %f %s", &t, &dt, &deadline, n);
		cont = 1;
		for (i = 0; result != EOF; i++){ 
			if (cont == maxSize) {
				process.threads = realloc(process.threads, 2*N);
				process.args = realloc(process.args, 2*N);
  				process.t = realloc(process.t, 2*N);
				process.dt = realloc(process.dt, 2*N);
  				process.deadline = realloc(process.deadline, 2*N);
  				maxSize *= 2;
			}
	    	printf("Aqui: %f %f %f %s \n", t, dt, deadline, n);
	    	process.args[i] = i;
	    	process.t[i] = t;
	    	process.dt[i] = dt;
	    	process.deadline[i] = deadline;
	    	resultCreation = pthread_create(&process.threads[i], NULL, oi, &process.args[i]);
	    	assert( !resultCreation );
	    	result = fscanf(arq, "%f %f %f %s", &t, &dt, &deadline, n);
	    	cont++;
		}
	}
	else {
		printf("Nops\n");
	}
}

int main(int argc, char *argv[ ]) {
	char *name;
	th process;
	//process = malloc (sizeof(th));
	if(argc == 2) {
		name = argv[1];
	}
	else {
		printf("Argumento inválido\n");
	}
	createThreads(name, process);
	
	return 0;
}
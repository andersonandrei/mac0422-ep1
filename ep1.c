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
#include <sys/time.h>

#include <pthread.h>
#include <assert.h>
#include <semaphore.h>

#include <sys/queue.h>

#define N 1024

// typedef struct {
// 	pthread_t *threads;
// 	pthread_mutex_t *mutex;
// 	int *id;
// 	char **name;
// 	float *t;
// 	float *dt;
// 	float *deadline;
// 	int qnt;
// 	int posTemp;
// }	th;

typedef struct {
	int id;
	char *name;
	float t, dt, deadline;
	pthread_t thread;
	pthread_mutex_t mutex;
} th;

th *process;
int qntProcess;

void printingInfo() {
	int i;
	printf("To aqui");
	fflush(stdout);
	for (i = 0; i < qntProcess; i++) {
		printf("Process %s : %f %f %f\n", process[i].name, process[i].t, process[i].dt, process[i].deadline);
	}
}

void* oi(void *argument){
	th *t = (th *) argument;
	printf("Oi sou uma thread %f \n", t->deadline);
	return 0;
}

void createThreads(char *name) {
  	FILE *arq;
  	int result, resultCreation;
  	int i;
  	int maxSize = N;
  	int cont = 0;
  	float t, dt, deadline;
  	char *n = malloc (1024 * sizeof(char));
 //  	process.threads = malloc(N * sizeof(pthread_t));
 //  	process.mutex = malloc(N * sizeof(pthread_mutex_t));
 //  	process.id = malloc(N * sizeof(int));
 //  	process.name = malloc(N * sizeof(char *));
 //  	process.t = malloc (N * sizeof(float));
 // 	process.dt = malloc (N * sizeof(float));
 //  	process.deadline = malloc (N * sizeof(float));

  	arq = fopen(name, "rt");
	if (arq != NULL) {
		result = fscanf(arq, "%f %f %f %s", &t, &dt, &deadline, n);
		cont = 1;
		for (i = 0; result != EOF; i++){ 
		//while(result != EOF) {
			// if (cont == maxSize) {
			// 	process.threads = realloc(process.threads, 2*N);
			// 	process.mutex = realloc(process.mutex, 2*N);
			// 	process.id = realloc(process.id, 2*N);
			// 	process.name = realloc(process.name, 2*N);
  	// 			process.t = realloc(process.t, 2*N);
			// 	process.dt = realloc(process.dt, 2*N);
  	// 			process.deadline = realloc(process.deadline, 2*N);
  	// 			maxSize *= 2;
			// }
			process[i].id = i;
	    	process[i].name = n;
	    	process[i].t = t;
	    	process[i].dt =  dt;
	    	process[i].deadline = deadline;
	    	printf("Process %s : %f %f %f\n", process[i].name, process[i].t, process[i].dt, process[i].deadline);
	    	resultCreation = pthread_create(&process[i].thread, NULL, &oi, &process[i]);
	    	pthread_join(process[i].thread, NULL);
	    	assert( !resultCreation );
	    	result = fscanf(arq, "%f %f %f %s", &t, &dt, &deadline, n);
	    	cont++;
		}
		qntProcess = cont-1;
		printf("guardei: %d\n", qntProcess);
	}
	else {
		printf("Nops\n");
	}
}

void destroyThreads() {
	int i;
	for (i = 0; i < qntProcess; i++) {
		free(process[i].name);
		//pthread_exit();//;;(process.threads[i]);
	}
	free(&process[i].thread);
	free(&process[i].name);
	free(&process[i].t);
	free(&process[i].dt);
	free(&process[i].deadline);
} 

void executeThreads() {
  	struct timeval tv;
  	//time_t seconds;
  	int i;

 	gettimeofday(&tv, NULL); 

 	printf("%ld\n" ,tv.tv_sec);

 	printf("qnt: %d" , qntProcess);
 	for (i = 0; i < qntProcess; i++) {
 		printf("Thread : %s\n", process[i].name);
 		pthread_join(process[i].thread, NULL);
 	}
}


int main(int argc, char *argv[ ]) {
	char *name;
	process = malloc (N * sizeof(th));
	if(argc == 2) {
		name = argv[1];
	}
	else {
		printf("Argumento inválido\n");
	}
	createThreads(name);
	printf("Qnt armazenada: %d \n", qntProcess);
	//executeThreads(&process);
	//printingInfo(process);
	//destroyThreads(process);


	return 0;
}
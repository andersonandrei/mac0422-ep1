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
#define __USE_GNU
#include <sys/time.h>
#include <sys/resource.h>

#include <pthread.h>
#include <assert.h>
#include <semaphore.h>

#include <sys/queue.h>
#include "queue.h"

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

void printingInfo() {
	int i;
	printf("To aqui");
	fflush(stdout);
	for (i = 0; i < qntProcess; i++) {
		printf("Process %s : %f %f %f\n", process[i].name, process[i].t, process[i].dt, process[i].deadline);
	}
}

void createThreads(char *name) {
  	FILE *arq;
  	int result;
  	int i;
  	int cont = 0;
  	float t, dt, deadline;
  	char *n = malloc (1024 * sizeof(char));
  	arq = fopen(name, "rt");
	if (arq != NULL) {
		result = fscanf(arq, "%f %f %f %s", &t, &dt, &deadline, n);
		cont = 1;
		for (i = 0; result != EOF; i++){ 
			process[i].id = i;
	    	process[i].name = n;
	    	printf("------ COlocnado em i: %d, o nome : %s\n", i, n);
	    	process[i].t = t;
	    	process[i].dt =  dt;
	    	process[i].deadline = deadline;
	    	printf("Process %s : %f %f %f\n", process[i].name, process[i].t, process[i].dt, process[i].deadline);
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

void enqueueThread(th thread) {
	struct node *p;
	p = malloc(sizeof(struct node));
	p->info = thread.dt;
	p->id = thread.id;
	enq(p);
	return;
}

void enqueueThreads(th *process) {
	int i;
	create();
	for (i = 0; i < qntProcess; i++) {
		printf("Empilhando %d - %s com dt: %f\n", i, process[i].name, process[i].dt);
		enqueueThread(process[i]);
	}
	return;
}

void* job(void *argument){
	struct rusage ru;
	struct timeval utime;
	float seconds = 0; 
	int i, j;
	th *t = (th *) argument;
	printf("Dentro do processo: thread %d-%s com dt: %f \n", t->id, t->name, t->dt);
	getrusage(RUSAGE_THREAD, &ru);
	utime = ru.ru_utime;
	printf("Peguei o time : %ld e %ld \n", utime.tv_sec, utime.tv_usec);
	while (seconds < (1 * t-> dt)) {
		//spend time
		for (i = 0; i < 10; i++) {
			j++;
		}
		getrusage(RUSAGE_THREAD, &ru);
		utime = ru.ru_utime;
		seconds = ru.ru_utime.tv_sec + ((float) ru.ru_utime.tv_usec / 1000000);
	}
	printf("Ficou : %f s\n", seconds);
	return 0;
}

void schedulerSJF(th *process) {
	int id;
	int result_code;
	int cont = qntProcess;
	printf("Escalonador ------------\n");
	enqueueThreads(process);
	removeAll();
	enqueueThreads(process);
	printf("Vendo fila\n");
	display();
	while (cont > 0) {
		id = deq();
		printf("Desempilhou %d agr ta com tamanho: %d\n", id, queuesize());
		if(pthread_mutex_init(&process[id].mutex, NULL) != 0) {
			printf("Erro ao criar\n");
		}
		else {
			printf("Vai criar a thread ----\n");
			pthread_mutex_lock(&process[id].mutex);
			result_code = pthread_create(&process[id].thread, NULL, &job, &process[id]);
			pthread_join(process[id].thread, NULL);
			pthread_mutex_unlock(&process[id].mutex);
		}
		cont--;
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
	schedulerSJF(process);
	//enqueueThreads(process);
	// enqueueThreads(process);
	// id = deq();
	// printf("Desempilhou %d - %s com dt: %f\n", id, process[id].name, process[id].dt);
	// id = deq();
	// printf("Desempilhou %d - %s com dt: %f\n", id, process[id].name, process[id].dt);
	// id = deq();
	// printf("Desempilhou %d - %s com dt: %f\n", id, process[id].name, process[id].dt);
	//executeThreads(&process);
	//printingInfo(process);
	//destroyThreads(process);


	return 0;
}
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

typedef struct {
  pthread_t *threads;
  pthread_mutex_t *mutex;
  char **name;
  float *t;
  float *dt;
  float *deadline;
  int qnt;
  int posTemp;
} th;

LIST_HEAD(listhead, entry) head;

struct entry {
  th dataThread;
  LIST_ENTRY(entry) entries;
};

void printingInfo(th *process) {
	int i;
	printf("To aqui");
	fflush(stdout);
	for (i = 0; i < process->qnt; i++) {
		printf("Process %s : %f %f %f\n", process->name[i], process->t[i], process->dt[i], process->deadline[i]);
	}
}

void* oi(void *argument){
	th *process = (th *) argument;
	printf("Oi sou uma thread %d : %f\n",process->posTemp, process->deadline[process->posTemp]);
	return 0;
}

void createThreads(char *name, th *process) {
  	FILE *arq;
  	int result, resultCreation;
  	int i;
  	int maxSize = N;
  	int cont = 0;
  	float t, dt, deadline;
  	char *n = malloc (1024 * sizeof(char));
  	process->threads = malloc(N * sizeof(pthread_t));
  	process->mutex = malloc(N * sizeof(pthread_mutex_t));
  	process->name = malloc(N * sizeof(char *));
  	process->t = malloc (N * sizeof(float));
	process->dt = malloc (N * sizeof(float));
  	process->deadline = malloc (N * sizeof(float));

  	arq = fopen(name, "rt");
	if (arq != NULL) {
		result = fscanf(arq, "%f %f %f %s", &t, &dt, &deadline, n);
		cont = 1;
		for (i = 0; result != EOF; i++){ 
		//while(result != EOF) {
			if (cont == maxSize) {
				process->threads = realloc(process->threads, 2*N);
				process->mutex = realloc(process->mutex, 2*N);
				process->name = realloc(process->name, 2*N);
  				process->t = realloc(process->t, 2*N);
				process->dt = realloc(process->dt, 2*N);
  				process->deadline = realloc(process->deadline, 2*N);
  				maxSize *= 2;
			}
	    	process->name[i] = n;
	    	process->t[i] = t;
	    	process->dt[i] =  dt;
	    	process->deadline[i] = deadline;
	    	process->posTemp = i;
	    	printf("Process %s : %f %f %f\n", process->name[i], process->t[i], process->dt[i], process->deadline[i]);
	    	resultCreation = pthread_create(&process->threads[i], NULL, &oi, process);
	    	pthread_join(process->threads[i], NULL);
	    	assert( !resultCreation );
	    	result = fscanf(arq, "%f %f %f %s", &t, &dt, &deadline, n);
	    	cont++;
		}
		process->qnt = cont-1;
		printf("guardei: %d\n", process->qnt);
	}
	else {
		printf("Nops\n");
	}
}

void destroyThreads(th *process) {
	int i;
	for (i = 0; i < process->qnt; i++) {
		free(process->name[i]);
		//pthread_exit();//;;(process->threads[i]);
	}
	free(process->threads);
	free(process->name);
	free(process->t);
	free(process->dt);
	free(process->deadline);
} 

void executeThreads(th *process) {
  	struct timeval tv;
  	//time_t seconds;
  	int i;

 	gettimeofday(&tv, NULL); 

 	printf("%ld\n" ,tv.tv_sec);

 	printf("qnt: %d" , process->qnt);
 	for (i = 0; i < process->qnt; i++) {
 		printf("Thread : %s\n", process->name[i]);
 		pthread_join(process->threads[i], NULL);
 	}
}

void enqueueThreads(th *process) {
	int i;
	LIST_INIT(&head);
	struct entry *elem;
	for(i = 0; i < process -> qnt; i++) {
		LIST_INSERT_HEAD(&head, process.threads[i], entrie);
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
	createThreads(name, &process);
	printf("Qnt armazenada: %d \n", process.qnt);
	//executeThreads(&process);
	//printingInfo(process);
	//destroyThreads(process);


	return 0;
}
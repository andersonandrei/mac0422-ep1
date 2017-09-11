#include "ep1.h"

thr *process;
int qntProcess;

void printingInfo() {
	int i;
	printf("To aqui");
	fflush(stdout);
	for (i = 0; i < qntProcess; i++) {
	}
}

void createThreads(char *name, int *qntProcess, int verbose) {
  	FILE *arq;
  	int result;
  	int i;
  	int cont = 0;
  	float t, dt, deadline;
  	char *n = malloc (1024 * sizeof(char));
  	arq = fopen(name, "rt");
	if (arq != NULL) {
		result = fscanf(arq, "%f %f %f %s", &t, &dt, &deadline, n);
		for (i = 0; result != EOF; i++){
			if(verbose) fprintf(stderr, ">> Processo inserido no sistema: %s - linha : %d\n", n, i);
			process[i].id = i;
	    	process[i].name = n;
	    	process[i].t = t;
	    	process[i].dt =  dt;
	    	process[i].deadline = deadline;
	    	//print("Process %s : %.2f %.2f %.2f\n", process[i].name, process[i].t, process[i].dt, process[i].deadline);
	    	cont++;
	    	n = malloc (1024 * sizeof(char));
	    	result = fscanf(arq, "%f %f %f %s", &t, &dt, &deadline, n);
		}
		*qntProcess = cont;
		//print("guardei: %d\n", *qntProcess);
	}
	else {
		//print("Nops\n");
	}
	fclose(arq);
}

void destroyThreads() {
	int i;
	for (i = 0; i < qntProcess; i++) {
		free(process[i].name);
		//p->read_exit();//;;(process.->reads[i]);
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
 	//print("%ld\n" ,tv.tv_sec);
 	//print("qnt: %d" , qntProcess);
 	for (i = 0; i < qntProcess; i++) {
 		//print("Thread : %s\n", process[i].name);
 		pthread_join(process[i].thread, NULL);
 	}
}

void enqueueThreadDt(thr thread, struct node **rear, struct node **front) {
	struct node *p;
	p = malloc(sizeof(struct node));
	p->info = thread.dt;
	p->id = thread.id;
	enq(p, rear, front);
	return;
}

void enqueueThreadT(thr thread, struct node **rear, struct node **front) {
	struct node *p;
	p = malloc(sizeof(struct node));
	p->info = thread.t;
	p->id = thread.id;
	enq(p, rear, front);
	return;
}

void enqueueThreads(thr *process, int qntProcess, struct node **rear, struct node **front) {
	int i;
	create(rear, front);
	for (i = 0; i < qntProcess; i++) {
		enqueueThreadT(process[i], rear, front);
	}
	return;
}

int main(int argc, char *argv[ ]) {
	char *name, *output, *d, *scheduler;
	process = malloc (N * sizeof(thr));
	if(argc >= 4) {
		scheduler = argv[1];
		name = argv[2];
		output = argv[3];
		if (argc == 5)
			d = argv[4];
	}
	else {
		printf("Argumento inválido\n");
	}
	//print("Qnt armazenada: %d e sche : %d\n", qntProcess, scheduler[0]);
	if(scheduler[0] == 49) // == 1
		schedulerSJF(process, name, output, d);
	if(scheduler[0] == 50)
		schedulerRoudRobin(process, name, output, d);
	if(scheduler[0] == 51)
		schedulerPriority(process, name, output, d);
	
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
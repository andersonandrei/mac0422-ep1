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

void createThreads(char *name, int *qntProcess) {
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
			fprintf(stderr, "Processo inserido no siste: %s - linha : %d\n", n, i);
			process[i].id = i;
	    	process[i].name = n;
	    	process[i].t = t;
	    	process[i].dt =  dt;
	    	process[i].deadline = deadline;
	    	printf("Process %s : %.2f %.2f %.2f\n", process[i].name, process[i].t, process[i].dt, process[i].deadline);
	    	cont++;
	    	n = malloc (1024 * sizeof(char));
	    	result = fscanf(arq, "%f %f %f %s", &t, &dt, &deadline, n);
		}
		*qntProcess = cont;
		printf("guardei: %d\n", *qntProcess);
	}
	else {
		printf("Nops\n");
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
 	printf("%ld\n" ,tv.tv_sec);
 	printf("qnt: %d" , qntProcess);
 	for (i = 0; i < qntProcess; i++) {
 		printf("Thread : %s\n", process[i].name);
 		pthread_join(process[i].thread, NULL);
 	}
}

int main(int argc, char *argv[ ]) {
	char *name, *output;
	process = malloc (N * sizeof(thr));
	if(argc == 3) {
		name = argv[1];
		output = argv[2];
	}
	else {
		printf("Argumento inválido\n");
	}
	printf("Qnt armazenada: %d \n", qntProcess);
	//schedulerSJF(process, name, output);
	schedulerRoudRobin(process, name, output);
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
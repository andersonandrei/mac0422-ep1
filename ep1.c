/* ep1 main */

#include "ep1.h"

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
		for (i = 0; result != EOF; i++){ 
			printf("Leu %s : %f %f %f\n", n, t, dt, deadline);
			process[i].id = i;
	    	process[i].name = n;
	    	printf("------ Colocnado em i: %d, o nome : %s\n", i, n);
	    	process[i].t = t;
	    	process[i].dt =  dt;
	    	process[i].deadline = deadline;
	    	printf("Process %s : %f %f %f\n", process[i].name, process[i].t, process[i].dt, process[i].deadline);
	    	cont++;
	    	n = malloc (1024 * sizeof(char));
	    	result = fscanf(arq, "%f %f %f %s", &t, &dt, &deadline, n);
		}
		qntProcess = cont;
		printf("guardei: %d\n", qntProcess);
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
		//pthread_exit();//;;(process.threads[i]);
	}
	free(&process[i].thread);
	free(&process[i].name);
	free(&process[i].t);
	free(&process[i].dt);
	free(&process[i].deadline);
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
	printf("Qnt armazenada: %d \n", qntProcess);
	schedulerSJF(process, name);
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
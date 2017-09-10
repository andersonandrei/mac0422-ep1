#include "schedulerPriority.h"

int prempcaoP = 0;

/*int calcQuantum (int t, int dt, int deadline) {
	int quantum;
	quantum = deadline - (t + dt);
	quantum = (quantum/1000) + 100;
	return quantum;
}*/

float calcQuantum (float t) {
	return t+(t*0.5);
}

void* jobP(void *argument){
	struct rusage ru;
	float quantum = 1;

	//struct timeval utime;
	float seconds = 0; 
	int i, j;
	thr *t = (thr *) argument;
	getrusage(RUSAGE_THREAD, &ru);
	seconds = 0;
	//utime = ru.ru_utime;

	while (seconds < (calcQuantum(t->t))) {
		for (i = 0; i < 10; i++) {
			j++;
		}
		getrusage(RUSAGE_THREAD, &ru);
		seconds = ru.ru_utime.tv_sec + ((float) ru.ru_utime.tv_usec / 1000000);
	}
	t->dt-=quantum;
	return 0;
}

void schedulerPriority(thr *process, char *name, char *output, char *d) {
	FILE *out;
	struct node *rearP, *frontP;
	struct node *rearPool, *frontPool;
	struct node *p;
	struct rusage ru;
	float begin, end, running, b, beginP = 0, endP = 0;
	int id;
	int result_code;
	int qntProcess;
	int cont;
	int i;
	int verif;
	int empty = 0;
	int control;
	int prempcao = 0;
	int linePrinted = 0;
	int parted = 0;
	int verbose;

	if (d[0] == 100) verbose = 1;
	rearPool = NULL;
	frontPool = NULL;
	rearP = NULL;
	frontP = NULL;
	createThreads(name, &qntProcess);

	printf("Escalonador ------------\n");
	enqueueThreads(process, qntProcess, &rearPool, &frontPool); //created the pool
	printf("Cont : %d", qntProcess);
	getrusage(RUSAGE_THREAD, &ru); //start the time
	b = ru.ru_utime.tv_sec + ((float) ru.ru_utime.tv_usec / 1000000) +
			ru.ru_stime.tv_sec + ((float) ru.ru_stime.tv_usec / 1000000);
	i = 0;
	printf("\n Size: %d\n", queuesize(rearPool, frontPool));
	out = fopen(output, "w");
	control = queuesize(rearPool, frontPool);
	printf("Control: %d\n", control);
	while (queuesize(rearPool, frontPool) > 0 || control > 0) {
		//printf("Control: %d", control);
		if (empty) {
			printf("Empty\n");
			return;
		}
		if (i == 0) {
			verif = deq(&rearPool, &frontPool);
			i = 1;
		}
		getrusage(RUSAGE_THREAD, &ru);
		running = ru.ru_utime.tv_sec + ((float) ru.ru_utime.tv_usec / 1000000) +
			ru.ru_stime.tv_sec + ((float) ru.ru_stime.tv_usec / 1000000);
		cont = 0;
		//printf("Time: %.2f\n", (running));
		while (process[verif].t <= (running-b) && !empty) {
			i = 0;
			if (verbose) printf(">> Processo %s recebido no sistema\n", process[verif].name);
			enqueueThreadDt(process[verif], &rearP, &frontP);
			cont++;
			if (queuesize(rearPool, frontPool) > 0) {
				verif = deq(&rearPool, &frontPool);
				i = 1;
			}
			else {
				//printf("Esvaziou a pilha\n");
				empty = 1;
			}
		}
		getrusage(RUSAGE_SELF, &ru); //start the time
		begin = ru.ru_utime.tv_sec + ((float) ru.ru_utime.tv_usec / 1000000) +
			ru.ru_stime.tv_sec + ((float) ru.ru_stime.tv_usec / 1000000);
		while (cont > 0) {
			id = deq(&rearP, &frontP);
			if(pthread_mutex_init(&process[id].mutex, NULL) != 0) {
				printf("Erro ao criar\n");
			}
			else {
				printf("Quantum: %f\n", (calcQuantum(process[id].t)));
				if (verbose) printf(">> Processo %s utilizando a CPU: 0. \n", process[id].name);
				pthread_mutex_lock(&process[id].mutex);
				result_code = pthread_create(&process[id].thread, NULL, &jobRR, &process[id]);
				pthread_join(process[id].thread, NULL);
				pthread_mutex_unlock(&process[id].mutex);
				if (verbose) printf(">> Processo %s liberando a CPU: 0. \n", process[id].name);
				getrusage(RUSAGE_SELF, &ru);
				end = ru.ru_utime.tv_sec + ((float) ru.ru_utime.tv_usec / 1000000) +
							ru.ru_stime.tv_sec + ((float) ru.ru_stime.tv_usec / 1000000);
				if (process[id].dt > 0) {
					//printf("Restou tempo pra name = %s\n", process[id].name);
					parted = 1;
					beginP = begin;
					endP += end-begin;
					printf("Endp ta com %.2f\n", endP );
					p = malloc(sizeof(struct node));
					p->info = process[id].dt;
					p->id = process[id].id;
					p->ptr = NULL;
					enq(p, &rearP, &frontP);
					cont++;
					control++;
					prempcao++;
				}
				else {
					if (verbose) printf(">> Processo %s finalizado. Escrevendo na linha %d do arquivo %s.\n", 
						process[id].name, linePrinted, output);
					if (parted) {
						printf("Endp fechou com %.2f\n", endP );
						fprintf(out, "%s %.2f %.2f \n", process[id].name, endP, endP-beginP);
						parted = 0;
						endP = 0;
					}
					else {
						fprintf(out, "%s %.2f %.2f \n", process[id].name, end, end-begin);
					}
					linePrinted++;
				}
				
			}
			cont--;
			control--;
		}
	}
	fclose(out);
	if (verbose) printf(">> Quantidade de mudanças de contexto: %d.\n", prempcao);
}
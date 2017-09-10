#include "schedulerRoudRobin.h"

void* jobRR(void *argument){
	struct rusage ru;
	float quantum = 1;

	//struct timeval utime;
	float seconds = 0; 
	int i, j;
	thr *t = (thr *) argument;
	getrusage(RUSAGE_THREAD, &ru);
	seconds = 0;
	//utime = ru.ru_utime;
	while (seconds < (quantum)) {
		for (i = 0; i < 10; i++) {
			j++;
		}
		getrusage(RUSAGE_THREAD, &ru);
		seconds = ru.ru_utime.tv_sec + ((float) ru.ru_utime.tv_usec / 1000000);
	}
	t->dt-=quantum;
	return 0;
}

void schedulerRoudRobin(thr *process, char *name, char *output, char *d) {
	FILE *out;
	struct node *rearRR, *frontRR;
	struct node *rearPool, *frontPool;
	struct node *p;
	struct rusage ru;
	//float begin, end, running, b;
	float beginP = 0, endP = 0;
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
	struct timeval tv;
	time_t curtime , running, begin, end, b;


	if (d[0] == 100) verbose = 1;
	rearPool = NULL;
	frontPool = NULL;
	rearRR = NULL;
	frontRR = NULL;
	createThreads(name, &qntProcess);

	printf("Escalonador ------------\n");
	enqueueThreads(process, qntProcess, &rearPool, &frontPool); //created the pool
	printf("Cont : %d", qntProcess);
	gettimeofday(&tv, NULL);
	b = tv.tv_sec;// + ((float)tv.tv_usec / 1000000);
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
		gettimeofday(&tv, NULL);
		running = tv.tv_sec;// + ((float)tv.tv_usec / 1000000);;
		cont = 0;
		//printf("Time: %.2f\n", (running));
		while (process[verif].t <= (running-b) && !empty) {
			i = 0;
			if (verbose) printf(">> Processo %s recebido no sistema\n", process[verif].name);
			enqueueThreadT(process[verif], &rearRR, &frontRR);
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
		gettimeofday(&tv, NULL);
		begin = tv.tv_sec;// + ((float)tv.tv_usec / 1000000);
		while (cont > 0) {
			id = deq(&rearRR, &frontRR);
			if(pthread_mutex_init(&process[id].mutex, NULL) != 0) {
				printf("Erro ao criar\n");
			}
			else {
				if (verbose) printf(">> Processo %s utilizando a CPU: 0. \n", process[id].name);
				pthread_mutex_lock(&process[id].mutex);
				result_code = pthread_create(&process[id].thread, NULL, &jobRR, &process[id]);
				pthread_join(process[id].thread, NULL);
				pthread_mutex_unlock(&process[id].mutex);
				if (verbose) printf(">> Processo %s liberando a CPU: 0. \n", process[id].name);
				gettimeofday(&tv, NULL);
				end = tv.tv_sec;// + ((float)tv.tv_usec / 1000000);;
				if (process[id].dt > 0) {
					//printf("Restou tempo pra name = %s\n", process[id].name);
					parted = 1;
					//beginP = begin-b;
					endP += end-begin;
					printf("Endp ta com %.2f\n", endP );
					p = malloc(sizeof(struct node));
					p->info = process[id].dt;
					p->id = process[id].id;
					p->ptr = NULL;
					enq(p, &rearRR, &frontRR);
					cont++;
					control++;
					prempcao++;
				}
				else {
					if (verbose) printf(">> Processo %s finalizado. Escrevendo na linha %d do arquivo %s.\n", 
						process[id].name, linePrinted, output);
					if (parted) {
						parted = 0;
						endP = 0;
					}

					fprintf(out, "%s %.2ld %.2ld\n", process[id].name, end-b, end-begin);
					linePrinted++;
				}
				/*
				else {
					if (verbose) printf(">> Processo %s finalizado. Escrevendo na linha %d do arquivo %s.\n", 
						process[id].name, linePrinted, output);
					if (parted) {
						printf("Endp fechou com %.2f\n", endP );
						fprintf(out, "%s %.2f %.2f \n", process[id].name, end-b, end-begin);
						parted = 0;
						endP = 0;
					}
					else {
						fprintf(out, "%s %.2ld %.2ld\n", process[id].name, end-b, end-begin);
					}
					linePrinted++;
				}*/
				
			}
			cont--;
			control--;
		}
	}
	fclose(out);
	if (verbose) printf(">> Quantidade de mudanças de contexto: %d.\n", prempcao);
}
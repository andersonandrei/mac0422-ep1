/*  EP1 - MAC0422 - Anderson Andrei da Silva
    Shell + Gerenciador de processos */

#include "schedulerPriority.h"

int prempcaoP = 0;
float quantumP = 1;

float calcQuantum (float t) {
	return t+(t*0.01);
}

void* jobP(void *argument){
	struct rusage ru;
	float seconds = 0; 
	int i, j;
	thr *t = (thr *) argument;
	getrusage(RUSAGE_THREAD, &ru);
	seconds = 0;
	while (seconds < 1) {
		for (i = 0; i < 10; i++) {
			j++;
		}
		getrusage(RUSAGE_THREAD, &ru);
		seconds = ru.ru_utime.tv_sec + ((float) ru.ru_utime.tv_usec / 1000000);
	}
	return 0;
}
void schedulerPriority(thr *process, char *name, char *output, char *d) {
	FILE *out;
	struct node *rearP, *frontP;
	struct node *rearPool, *frontPool;
	struct node *p;
	int id, verif;
	int result_code;
	int qntProcess;
	int cont, control, linePrinted = 0;
	int i, j;
	int empty = 0, prempcao = 0;
	int verbose, parted = 0;
	struct timeval tv;
	time_t curtime , running, begin, end, b;
	time_t *timeThreads;

	if (d[0] == 100) verbose = 1;
	rearPool = NULL;
	frontPool = NULL;
	rearP = NULL;
	frontP = NULL;
	createThreads(name, &qntProcess, verbose);
	enqueueThreads(process, qntProcess, &rearPool, &frontPool);
	gettimeofday(&tv, NULL);
	b = tv.tv_sec;
	i = 0; //to deq in main while
	out = fopen(output, "w");
	control = queuesize(rearPool, frontPool);
	timeThreads = malloc(control * sizeof(time_t));
	for (j = 0; j < control; j++) {
		timeThreads[j] = 0;
	}
	cont = 0; //It's used when Pool is empty but Have think to do.
	while (queuesize(rearPool, frontPool) > 0 || control > 0) {
		if (i == 0 && !empty) {
			verif = deq(&rearPool, &frontPool);
			i = 1;
		}
		gettimeofday(&tv, NULL);
		running = tv.tv_sec;
		while (process[verif].t <= (running-b) && !empty) {
			enqueueThreadT(process[verif], &rearP, &frontP);
			cont++;
			if (queuesize(rearPool, frontPool) > 0) {
				verif = deq(&rearPool, &frontPool);
				i = 1;
			}
			else {
				empty = 1;
			}
		}
		if (cont > 0) {
			id = deq(&rearP, &frontP);
			if(pthread_mutex_init(&process[id].mutex, NULL) != 0) {
				printf("Erro ao criar thread\n");
			}
			else {
				if (verbose) fprintf(stderr, ">> Processo %s utilizando a CPU: 0. \n", process[id].name);
				pthread_mutex_lock(&process[id].mutex);
				result_code = pthread_create(&process[id].thread, NULL, &jobP, &process[id]);
				pthread_join(process[id].thread, NULL);
				if (verbose) fprintf(stderr, ">> Processo %s liberando a CPU: 0. \n", process[id].name);
				pthread_mutex_unlock(&process[id].mutex);
				process[id].dt -= quantumP;
				gettimeofday(&tv, NULL);
				end = tv.tv_sec;
				if (process[id].dt > 0) {
					p = malloc(sizeof (struct node *));
					p -> info = process[id].t;
					p -> id = id;
					enq(p, &rearP, &frontP);
					cont++;
					control++;
					prempcao++;
				}
				else {
					if (verbose) fprintf(stderr, ">> Processo %s finalizado. Escrevendo na linha %d do arquivo %s.\n", 
						process[id].name, linePrinted, output);
					timeThreads[id] = end-b;
					fprintf(out, "%s %.2ld %.2ld\n", process[id].name, timeThreads[id], timeThreads[id]-((time_t)process[id].t));
					linePrinted++;
				}
				cont--;
				control--;
				fflush(stdout);
			}
		}
	}
	fprintf(out, "%d\n", prempcao);
	fclose(out);
	if (verbose) fprintf(stderr, ">> Quantidade de mudanças de contexto: %d.\n", prempcao);
}
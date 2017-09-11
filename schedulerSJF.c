/*  EP1 - MAC0422 - Anderson Andrei da Silva
    Shell + Gerenciador de processos */

#include "schedulerSJF.h"

void* job(void *argument){
	struct rusage ru;
	float seconds = 0; 
	int i, j;
	thr *t = (thr *) argument;
	seconds = 0;
	while (seconds < (1 * t-> dt)) {
		for (i = 0; i < 10; i++) {
			j++;
		}
		getrusage(RUSAGE_THREAD, &ru);
		seconds = ru.ru_utime.tv_sec + ((float) ru.ru_utime.tv_usec / 1000000) +
			ru.ru_stime.tv_sec + ((float) ru.ru_stime.tv_usec / 1000000);
	}
	return 0;
}

void schedulerSJF(thr *process, char *name, char *output, char *d) {
	FILE *out;
	struct node *rearSJF, *frontSJF;
	struct node *rearPool, *frontPool;
	struct rusage ru;
	int id, verif;
	int result_code;
	int qntProcess, cont, control;
	int i, verbose;  
	int empty = 0, prempcao = 0;
	int linePrinted = 0;
	char buffer[30];
	struct timeval tv;
	time_t curtime , running, begin, end, b;

	if (d[0] == 100) verbose = 1;
	rearPool = NULL;
	frontPool = NULL;
	rearSJF = NULL;
	frontSJF = NULL;
	createThreads(name, &qntProcess, verbose);

	enqueueThreads(process, qntProcess, &rearPool, &frontPool); //created the pool
	gettimeofday(&tv, NULL);
	b = tv.tv_sec;
	i = 0;
	out = fopen(output, "w");
	control = queuesize(rearPool, frontPool);
	cont = 0;
	while (queuesize(rearPool, frontPool) > 0 || control > 0) {
		if (i == 0 && !empty) {
			verif = deq(&rearPool, &frontPool);
			i = 1;
		}
		gettimeofday(&tv, NULL);
		running = tv.tv_sec;
		while (process[verif].t <= (running-b) && !empty) {
			if (verbose) fprintf(stderr, ">> Processo %s recebido no sistema\n", process[verif].name);
			i = 0;
			enqueueThreadDt(process[verif], &rearSJF, &frontSJF);
			cont++;
			if (queuesize(rearPool, frontPool) > 0) {
				verif = deq(&rearPool, &frontPool);
				i = 1;
			}
			else {
				empty = 1;
			}
		}
		gettimeofday(&tv, NULL);
		begin = tv.tv_sec;
		if (cont > 0) {
			id = deq(&rearSJF, &frontSJF);
			if(pthread_mutex_init(&process[id].mutex, NULL) != 0) {
				printf("Erro ao criar thread\n");
			}
			else {
				if (verbose) fprintf(stderr, ">> Processo %s utilizando a CPU: 0. \n", process[id].name);
				pthread_mutex_lock(&process[id].mutex);
				result_code = pthread_create(&process[id].thread, NULL, &job, &process[id]);
				pthread_join(process[id].thread, NULL);
				if (verbose) fprintf(stderr, ">> Processo %s liberando a CPU: 0. \n", process[id].name);
				if (verbose) fprintf(stderr, ">> Processo %s finalizado. Escrevendo na linha %d do arquivo %s.\n", 
					process[id].name, linePrinted, output);
				fprintf(out, "%s ", process[id].name);
				pthread_mutex_unlock(&process[id].mutex);
			}
			gettimeofday(&tv, NULL);
			end = tv.tv_sec;
			fprintf(out, "%2.2ld %2.2ld \n", end-b, end-b-(time_t)process[id].t);
			linePrinted++;
			cont--;
			control--;
		}
	}
	fprintf(out, "%d\n", prempcao);
	fclose(out);
	if (verbose) fprintf(stderr, ">> Quantidade de mudanças de contexto: %d.\n", prempcao);
		
}
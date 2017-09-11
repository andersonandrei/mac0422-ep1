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
	//float begin, end, running, b;
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
	int verbose;  
	char buffer[30];
	struct timeval tv;
	time_t curtime , running, begin, end, b;

	printf(" Aqui %c e %d\n", d[0], d[0]);
	if (d[0] == 100) verbose = 1;
	rearPool = NULL;
	frontPool = NULL;
	rearSJF = NULL;
	frontSJF = NULL;
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
	cont = 0;
	while (queuesize(rearPool, frontPool) > 0 || control > 0) {

		if (empty) {
			printf("Empty\n");
			//return;
		}
		if (i == 0 && !empty) {
			printf("Pegou no i = 0\n");
			verif = deq(&rearPool, &frontPool);
			i = 1;
		}
		gettimeofday(&tv, NULL);
		running = tv.tv_sec;// + ((float)tv.tv_usec / 1000000);;
		//running = 0;
		//cont = 0;
		//b = 0;
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
				printf("Esvaziou a pilha\n");
				empty = 1;
			}
		}
		/*getrusage(RUSAGE_SELF, &ru); //start the time
		begin = ru.ru_utime.tv_sec + ((float) ru.ru_utime.tv_usec / 1000000) +
			ru.ru_stime.tv_sec + ((float) ru.ru_stime.tv_usec / 1000000);
		*/
		gettimeofday(&tv, NULL);
		begin = tv.tv_sec;// + ((float)tv.tv_usec / 1000000);
		//while (cont > 0) {
		if (cont > 0) {
			printf("Tem coisa na oficial\n");
			id = deq(&rearSJF, &frontSJF);
			if(pthread_mutex_init(&process[id].mutex, NULL) != 0) {
				printf("Erro ao criar\n");
			}
			else {
				//if (verbose) printf(">> Processo %s utilizando a CPU: 0. \n", process[id].name);
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
			end = tv.tv_sec;// + ((float)tv.tv_usec / 1000000);;
			printf("Begin com : %.2ld e encerrou com : %.2ld\n", begin-b, end-b);
			fprintf(out, "%2.2ld %2.2ld \n", end-b, end-begin);
			linePrinted++;
			cont--;
			control--;
		}
	}
	fprintf(out, "%d\n", prempcao);
	fclose(out);
	if (verbose) fprintf(stderr, ">> Quantidade de mudanças de contexto: %d.\n", prempcao);
		
}
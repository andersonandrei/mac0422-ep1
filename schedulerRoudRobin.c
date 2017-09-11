#include "schedulerRoudRobin.h"

float quantum = 1;

void* jobRR(void *argument){
	struct rusage ru;
	//float quantum = 1;

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
	//t->dt-=quantum;
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
	int i, j;
	int verif;
	int empty = 0;
	int control;
	int prempcao = 0;
	int linePrinted = 0;
	int parted = 0;
	int verbose;
	struct timeval tv;
	time_t curtime , running, begin, end, b;
	time_t *timeThreads;

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
	i = 0; //to deq in main while

	printf("\n Size: %d\n", queuesize(rearPool, frontPool));

	out = fopen(output, "w");
	control = queuesize(rearPool, frontPool);
	timeThreads = malloc(control * sizeof(time_t));
	for (j = 0; j < control; j++) {
		timeThreads[j] = 0;
	}
	cont = 0; //It's used when Pool is empty but Have think to do.

	printf("Control: %d\n", control);
	while (queuesize(rearPool, frontPool) > 0 || control > 0) {
		if (i == 0 && !empty) {
			printf("Quer desempilhar de i = 0\n");
			verif = deq(&rearPool, &frontPool);
			printf("Desempilhou do pool em i = 0: %s\n", process[verif].name);
			i = 1;
		}
		
		gettimeofday(&tv, NULL);
		running = tv.tv_sec;
		//print("Na mão: %d com t: %f e time %.2ld, true? : %d\n", verif, process[verif].t, running-b, process[verif].t <= running-b);
		//cont = 0;
		//printf("Time : %.2ld\n", running-b);
		while (process[verif].t <= (running-b) && !empty) {
			printf("Entrou pra empilhar na oficial: %s - id: %d\n", process[verif].name, verif);
			enqueueThreadT(process[verif], &rearRR, &frontRR);
			cont++;
			printf("\n Somou cont: %d\n", cont);
			if (queuesize(rearPool, frontPool) > 0) {
				verif = deq(&rearPool, &frontPool);
				printf("Pegou novo da pool : %d\n", verif);
				i = 1;
			}
			else {
				printf("Esvaziou Pool\n");
				empty = 1;
			}
		}

		gettimeofday(&tv, NULL);
		begin = tv.tv_sec;

		if (cont > 0) {

			printf("Tem coisa na oficial: %d\n", queuesize(&rearRR, &frontRR));
			id = deq(&rearRR, &frontRR);
			printf("Desempilhou da oficial : %s\n", process[id].name);
			if(pthread_mutex_init(&process[id].mutex, NULL) != 0) {
				printf("Erro ao criar\n");
			}
			else {
				if (verbose) fprintf(stderr, ">> Processo %s utilizando a CPU: 0. \n", process[id].name);
				pthread_mutex_lock(&process[id].mutex);
				result_code = pthread_create(&process[id].thread, NULL, &job, &process[id]);
				pthread_join(process[id].thread, NULL);
				if (verbose) fprintf(stderr, ">> Processo %s liberando a CPU: 0. \n", process[id].name);
				if (verbose) fprintf(stderr, ">> Processo %s finalizado. Escrevendo na linha %d do arquivo %s.\n", 
					process[id].name, linePrinted, output);
				//fprintf(out, "%s ", process[id].name);
				pthread_mutex_unlock(&process[id].mutex);
				process[id].dt -= quantum;
				gettimeofday(&tv, NULL);
				end = tv.tv_sec;
				timeThreads[id] += (end-begin);
				printf("Somou no vetor de tempos\n");
				if (process[id].dt > 0) {
					printf("Reinseriu %s no fundo, dt ta: %f\n", process[id].name, process[id].dt);
					p = malloc(sizeof (struct node *));
					p -> info = process[id].t;
					p -> id = id;
					enqEnd(p, &rearRR, &frontRR);
					cont++;
					control++;
					printf("\n Somou cont: %d e control %d\n", cont, control);
					prempcao++;
				}
				else {
					if (verbose) printf(">> Processo %s finalizado. Escrevendo na linha %d do arquivo %s.\n", 
						process[id].name, linePrinted, output);
					fprintf(out, "%s %.2ld %.2ld\n", process[id].name, timeThreads[id], end-begin);
					linePrinted++;
				}
				printf("Subtraiu\n");
				cont--;
				control--;
				printf("Cont e control: %d %d ", cont, control);
				fflush(stdout);
			}
		}
	}
	fprintf(out, "%d\n", prempcao);
	fclose(out);
	if (verbose) fprintf(stderr, ">> Quantidade de mudanças de contexto: %d.\n", prempcao);
}
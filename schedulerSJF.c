#include "schedulerSJF.h"

void enqueueThreadDt(thr thread, struct node **rearSJF, struct node **frontSJF) {
	struct node *p;
	p = malloc(sizeof(struct node));
	p->info = thread.dt;
	p->id = thread.id;
	enq(p, rearSJF, frontSJF);
	return;
}

void enqueueThreadT(thr thread, struct node **rearSJF, struct node **frontSJF) {
	struct node *p;
	p = malloc(sizeof(struct node));
	p->info = thread.t;
	p->id = thread.id;
	enq(p, rearSJF, frontSJF);
	return;
}

void enqueueThreads(thr *process, int qntProcess, struct node **rearSJF, struct node **frontSJF) {
	int i;
	create(rearSJF, frontSJF);
	for (i = 0; i < qntProcess; i++) {
		enqueueThreadT(process[i], rearSJF, frontSJF);
	}
	return;
}

void* job(void *argument){
	struct rusage ru;

	time_t tim = time(NULL);
	char dateBuffer[80];
	struct tm *tm = localtime(&tim);
	time(&tim);
	tm = localtime(&tim);

	strftime(dateBuffer,80," %I:%M:%S ", tm);
	//printf("Horário : %s\n", dateBuffer);

	//struct timeval utime;
	float seconds = 0; 
	int i, j;
	thr *t = (thr *) argument;
	getrusage(RUSAGE_THREAD, &ru);
	seconds = 0;
	//utime = ru.ru_utime;
	//printf("\n Começou job : %s em %.2f", t->name, clock()/(double)CLOCKS_PER_SEC);
	while (seconds < (1 * t-> dt)) {
		for (i = 0; i < 10; i++) {
			j++;
		}
		getrusage(RUSAGE_THREAD, &ru);
		seconds = ru.ru_utime.tv_sec + ((float) ru.ru_utime.tv_usec / 1000000);
	}
	//printf("Ficou : %.2f s\n", seconds);
	//printf("Saiu: \n");
	return 0;
}

void schedulerSJF(thr *process, char *name, char *output) {
	struct node *rearSJF, *frontSJF;
	struct node *rearPool, *frontPool;
	struct rusage ru;
	float begin, end, running, b;
	int id;
	int result_code;
	int qntProcess;
	int cont;
	int i;
	int verif;
	int processed = 0;
	int empty;
	int control;

	rearPool = NULL;
	frontPool = NULL;
	rearSJF = NULL;
	frontSJF = NULL;
	createThreads(name, &qntProcess);

	printf("Escalonador ------------\n");
	//printf("No scheduler: thread %d-%s com dt: %f \n", process[0].id, process[0].name, process[0].dt);
	enqueueThreads(process, qntProcess, &rearPool, &frontPool); //created the pool
	printf("Cont : %d", qntProcess);
	getrusage(RUSAGE_SELF, &ru); //start the time
	b = ru.ru_utime.tv_sec + ((float) ru.ru_utime.tv_usec / 1000000) +
			ru.ru_stime.tv_sec + ((float) ru.ru_stime.tv_usec / 1000000);
	i = 0;
	printf("\n Size: %d\n", queuesize(rearPool, frontPool));
/*	while (queuesize(rearPool, frontPool) > 0) {
		verif = deq(&rearPool, &frontPool);
		printf("Desempilhou : %d", process[verif].id);
	}*/
	processed = 1;
	control = queuesize(rearPool, frontPool);
	while (queuesize(rearPool, frontPool) > 0 || control > 0) {
		//printf("Entrou : %d\n", queuesize(rearPool, frontPool));
		if (empty) {
			//printf("Empty\n");
			return;
		}
		if (i == 0) {
			verif = deq(&rearPool, &frontPool);
			i = 1;
		}
		getrusage(RUSAGE_SELF, &ru);
		running = ru.ru_utime.tv_sec + ((float) ru.ru_utime.tv_usec / 1000000) +
			ru.ru_stime.tv_sec + ((float) ru.ru_stime.tv_usec / 1000000);
		cont = 0;
		//printf("Time: %.2f\n", (running));
		while (process[verif].t <= (running-b) && !empty) {
			i = 0;
			printf("\n Empilhou na oficial : %s\n", process[verif].name);
			enqueueThreadDt(process[verif], &rearSJF, &frontSJF);
			cont++;
			if (queuesize(rearPool, frontPool) > 0) {
				verif = deq(&rearPool, &frontPool);
				printf("Pegou novo : %s\n", process[verif].name);
				processed = 0;
				i = 1;
			}
			else {
				printf("Esvaziou a pilha\n");
				empty = 1;
			}
		}
		//if (verif ==  -1) break;
		while (cont > 0) {
			processed = 1;
			//printf("Executou\n");
			id = deq(&rearSJF, &frontSJF);
			if(pthread_mutex_init(&process[id].mutex, NULL) != 0) {
				printf("Erro ao criar\n");
			}
			else {
				printf("\n Executando thread: %s \n", process[id].name);
				pthread_mutex_lock(&process[id].mutex);
				result_code = pthread_create(&process[id].thread, NULL, &job, &process[id]);
				pthread_join(process[id].thread, NULL);
				// fprintf(out, process[id].name);
				// getrusage(RUSAGE_THREAD, &ru);
				// utime = ru.ru_utime;
				// fputc(tim1, out);
				// fputc(time2, out);
				pthread_mutex_unlock(&process[id].mutex);
			}
			//getrusage(RUSAGE_THREAD, &ru);
			end = ru.ru_utime.tv_sec + ((float) ru.ru_utime.tv_usec / 1000000) +
				ru.ru_stime.tv_sec + ((float) ru.ru_stime.tv_usec / 1000000);
			printf("Encerrou com : %.2f\n", end-begin);
			//getrusage(RUSAGE_THREAD, &ru);
			begin = ru.ru_utime.tv_sec + ((float) ru.ru_utime.tv_usec / 1000000) +
				ru.ru_stime.tv_sec + ((float) ru.ru_stime.tv_usec / 1000000);
			cont--;
			control--;
		}
	}
		
}
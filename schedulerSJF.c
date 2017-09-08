#include "schedulerSJF.h"

void enqueueThread(thr thread) {
	struct node *p;
	p = malloc(sizeof(struct node));
	p->info = thread.dt;
	p->id = thread.id;
	printf("Empilhando espec %d - %f\n", p->id, p->info);
	enq(p);
	return;
}

void enqueueThreads(thr *process, int qntProcess) {
	int i;
	create();
	for (i = 0; i < qntProcess; i++) {
		printf("----Empilhando %d - %s com dt: %f\n", i, process[i].name, process[i].dt);
		enqueueThread(process[i]);
	}
	return;
}

void* job(void *argument){
	struct rusage ru;
	struct timeval utime;
	float seconds = 0; 
	int i, j;
	thr *t = (thr *) argument;
	printf("Dentro do processo: thread %d-%s com dt: %f \n", t->id, t->name, t->dt);
	getrusage(RUSAGE_THREAD, &ru);
	utime = ru.ru_utime;
	//printf("Iniciou processamento : %ld \n", ru.ru_utime.tv_sec + ru.ru_utime.tv_usec);
	while (seconds < (1 * t-> dt)) {
		for (i = 0; i < 10; i++) {
			j++;
		}
		getrusage(RUSAGE_THREAD, &ru);
		utime = ru.ru_utime;
		seconds = ru.ru_utime.tv_sec + ((float) ru.ru_utime.tv_usec / 1000000);
	}
	printf("Ficou : %f s\n", seconds);
	return 0;
}

void schedulerSJF(thr *process, char *name, char *output) {
	struct rusage ru;;
	float begin, end;
	int id;
	int result_code;
	int qntProcess;
	int cont;
	//time_t begin, end;
	createThreads(name, &qntProcess);
	printf("Escalonador ------------\n");
	//Xprintf("No scheduler: thread %d-%s com dt: %f \n", process[0].id, process[0].name, process[0].dt);
	enqueueThreads(process, qntProcess);
	cont = qntProcess;
	printf("Cont : %d", cont);
	getrusage(RUSAGE_THREAD, &ru);
	begin = ru.ru_utime.tv_sec + ((float) ru.ru_utime.tv_usec / 1000000) +
			ru.ru_stime.tv_sec + ((float) ru.ru_stime.tv_usec / 1000000);
	//out = fopen(output, "w");
	//begin = clock();
	while (cont > 0) {
		id = deq();
		printf("Iniciou com %f\n", begin);
		printf("Desempilhou %d agr ta com tamanho: %d\n", id, queuesize());
		if(pthread_mutex_init(&process[id].mutex, NULL) != 0) {
			printf("Erro ao criar\n");
		}
		else {
			printf("Vai criar a thread ----\n");
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
		printf("Encerrou com : %f\n", end-begin);
		//getrusage(RUSAGE_THREAD, &ru);
		begin = ru.ru_utime.tv_sec + ((float) ru.ru_utime.tv_usec / 1000000) +
			ru.ru_stime.tv_sec + ((float) ru.ru_stime.tv_usec / 1000000);
		cont--;
	}
}
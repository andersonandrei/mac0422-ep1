/* Scheduler SJF*/
#include "schedulerSJF.h"

void enqueueThread(th thread) {
	struct node *p;
	p = malloc(sizeof(struct node));
	p->info = thread.dt;
	p->id = thread.id;
	printf("Empilhando espec %d - %f\n", p->id, p->info);
	enq(p);
	return;
}

void enqueueThreads(th *process) {
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
	th *t = (th *) argument;
	printf("Dentro do processo: thread %d-%s com dt: %f \n", t->id, t->name, t->dt);
	getrusage(RUSAGE_THREAD, &ru);
	utime = ru.ru_utime;
	printf("Peguei o time : %ld e %ld \n", utime.tv_sec, utime.tv_usec);
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

void schedulerSJF(th *process, char *name) {
	int id;
	int result_code;
	int cont = qntProcess;
	createThreads(name);
	cont = qntProcess;
	printf("Escalonador ------------\n");
	//Xprintf("No scheduler: thread %d-%s com dt: %f \n", process[0].id, process[0].name, process[0].dt);
	enqueueThreads(process);
	printf("Cont : %d", cont);
	while (cont > 0) {
		printf("No while \n");
		id = deq();
		printf("Desempilhou %d agr ta com tamanho: %d\n", id, queuesize());
		if(pthread_mutex_init(&process[id].mutex, NULL) != 0) {
			printf("Erro ao criar\n");
		}
		else {
			printf("Vai criar a thread ----\n");
			pthread_mutex_lock(&process[id].mutex);
			result_code = pthread_create(&process[id].thread, NULL, &job, &process[id]);
			pthread_join(process[id].thread, NULL);
			pthread_mutex_unlock(&process[id].mutex);
		}
		cont--;
	}
}

#ifndef SCHEDULERSJF_H
#define SCHEDULERSJF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //current dir
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <grp.h>
#include <time.h>
#define __USE_GNU
#include <sys/time.h>
#include <sys/resource.h>

#include <pthread.h>
#include <assert.h>
#include <semaphore.h>

#include <sys/queue.h>
#include "structs.h"
#include "queue.h"
#include "ep1.h"

void enqueueThreadDt(thr thread, struct node **rearSJF, struct node **frontSJF);

void enqueueThreadT(thr thread, struct node **rearSJF, struct node **frontSJF);

void enqueueThreads(thr *process, int qntProcess, struct node **rearSJF, struct node **frontSJF);

void* job(void *argument);

void schedulerSJF(thr *process, char *name, char *output);

/*while (cont > 0) {
			printf("Executou\n");
			id = deq(&rearSJF, &frontSJF);
			if(pthread_mutex_init(&process[id].mutex, NULL) != 0) {
				printf("Erro ao criar\n");
			}
			else {
				printf("\n Vai criar thread: %s \n", process[id].name);
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
		}*/


#endif
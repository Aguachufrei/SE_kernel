#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "scheduler.h"
#include "clock.h"


//inicialization
pthread_mutex_t mutexC = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
int tmpCount = 3;
int done = 0;
int se_time = 1;

void *clk(void *args){
#ifdef INIT
	printf("clock initialized\n");
#endif
	while (1) {
		pthread_mutex_lock(&mutexC);
		while (tmpCount > done){
			pthread_cond_wait(&cond1, &mutexC);
		}
		se_time++;
#ifdef TICK	
		printf("\nclk(%d): ",se_time);
#endif
#ifdef SLOW
		usleep(200000);
#endif
		done = 0;
		pthread_cond_broadcast(&cond2);
		pthread_mutex_unlock(&mutexC);
	}
}

void *stopwatch(void *args){
	struct temp_arg *argstruct = (struct temp_arg *)args;
	pthread_mutex_lock(&mutexC);
	int i= 0;
	while (1) {
		i++;
		done++;
		if(i==argstruct->frequency){
			i = 0;
#ifdef TICK
			printf(" <-- tclk ( %d )",argstruct->frequency);
#endif
			if (argstruct->function != NULL) {
				argstruct->function();
			}
		}
		pthread_cond_signal(&cond1);
		pthread_cond_wait(&cond2, &mutexC);
	}
}

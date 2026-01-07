#include <semaphore.h>
#include <unistd.h>
#include "process.h"
#include "clock.h"
#include "cpu.h"

sem_t mutexS;

void *scheduler(void *args) {
	sem_init(&mutexS, 1, 0);
	while(1) {
		sem_wait(&mutexS);
		pthread_mutex_lock(&cpu_mutex);
		//Prozesagailuen dauden aginduak berreskuratu
		for(int i = 0; i<cpu.coreNum; i++){
			for(int j = 0; j<cpu.hthreadNum; j++){
				if(cpu.cores[i][j]==NULL)continue;
				if(!cpu.cores[i][j]->hasCode){
					process_destroy(cpu.cores[i][j]);
					cpu.cores[i][j] = NULL;
					continue;
				}
				process_push(&ready, cpu.cores[i][j]);
				cpu.cores[i][j] = NULL;
			}
		}
#ifdef QUEE
		process_print(&ready);
#endif
		for(int i = 0; i<cpu.coreNum; i++){
			for(int j = 0; j<cpu.hthreadNum; j++){
				
				struct process_node *current = ready.first;
				if(current == NULL){
					continue;
				}

				struct process_node *best = current;
				struct process_node *previous = current;
				struct process_node *previousBest = current;
				int max_value = current->pcb->priority + se_time - current->pcb->lastTime;        

				while((current = process_get_next(current)) != NULL){
					if(current->pcb->priority + se_time - current->pcb->lastTime > max_value){
						best = current;
						previousBest = previous;
						max_value = current->pcb->priority + se_time - current->pcb->lastTime;        
					}  
					previous=current;
				}
				best->pcb->lastTime = se_time;
				struct PCB *bestpcb;
				if(best == previousBest){
					bestpcb = process_poll(&ready);
				} else { 
					bestpcb = process_destroy_next(&ready, previousBest);
				}
				cpu.cores[i][j]=bestpcb;
#ifdef QUEP
				process_print(&ready);
				printf("Best process is: %d, priority (%d) \n\n", bestpcb->id, max_value);
#endif
			}
		}
		pthread_mutex_unlock(&cpu_mutex);
	}
}


void call_scheduler(){
#ifdef INIT
	printf("scheduler initialized\n");
#endif
	sem_post(&mutexS);
}

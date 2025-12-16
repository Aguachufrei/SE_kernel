#include <semaphore.h>
#include <stdio.h>
#include "prozesuak.h"
#include "erlojua.h"
#include "cpu.h"
sem_t mutexS;


void *scheduler(void *args) {
	sem_init(&mutexS, 1, 0);
	while(1) {
		sem_wait(&mutexS);
		printf(" scheduler called...");
		//Prozesagailuen dauden aginduak berreskuratu
		for(int i = 0; i<cpu.coreNum; i++){
			for(int j = 0; j<cpu.hthreadNum; j++){
				if(cpu.cores[i][j]==NULL)continue;
				printf("hau ondo?");
				printf("\nbueltatzen da %d", cpu.cores[i][j]->id);
				prozesu_push(&ready, cpu.cores[i][j]);
			}
		}
#ifndef RR
		for(int i = 0; i<cpu.coreNum; i++){
			for(int j = 0; j<cpu.hthreadNum; j++){
				struct prozesu_ilara_node *current = ready.first;
				if(current == NULL){
					printf("no candidates found");
					continue;
				}

				struct prozesu_ilara_node *best = current;
				struct prozesu_ilara_node *previous = current;
				struct prozesu_ilara_node *previousBest = current;
				int max_value = current->pcb.priority + ssa_time - current->pcb.lastTime;        

				while((current = prozesu_get_next(current)) != NULL){
					if(current->pcb.priority + ssa_time - current->pcb.lastTime > max_value){
						best = current;
						previousBest = current;
						max_value = current->pcb.priority +ssa_time -current->pcb.lastTime;        
					}  
					previous=current;

				}
				printf("THE BEST :%d; T: %d P: %d", best->pcb.id, best->pcb.lastTime, best->pcb.priority);
				best->pcb.lastTime = ssa_time;
				prozesu_destroy_next(&ready, previousBest);
				cpu.cores[i][j]=&best->pcb;
			}
		}
#else
		struct PCB hurrengoprograma = prozesu_poll(&ready);
		prozesu_push(&ready, &hurrengoprograma);
#endif
	}
}
void call_scheduler(){
	sem_post(&mutexS);
}


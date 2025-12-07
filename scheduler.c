#include <semaphore.h>
#include <stdio.h>
#include "prozesuak.h"
#include "erlojua.h"
sem_t mutexS;


void *scheduler(void *args) {
    sem_init(&mutexS, 1, 0);
    while(1) {
        sem_wait(&mutexS);
        printf(" scheduler called...");
#ifndef RR
        struct prozesu_ilara_node *current = ready.first;
        if(current == NULL){
            printf("no candidates found");
            continue;
        }
        struct prozesu_ilara_node *best = current;
        int max_value = current->pcb.priority + ssa_time - current->pcb.lastTime;        

        while((current = prozesu_get_next(current)) != NULL){
            if(current->pcb.priority + ssa_time - current->pcb.lastTime > max_value){
                best = current;
                max_value = current->pcb.priority + ssa_time - current->pcb.lastTime;        
            }  
        }
        printf("THE BEST :%d; T: %d P: %d", best->pcb.id, best->pcb.lastTime, best->pcb.priority);
        best->pcb.lastTime = ssa_time;
#else
        struct PCB hurrengoprograma = prozesu_poll(&ready);
        prozesu_push(&ready, &hurrengoprograma);
#endif
    }
}
void call_scheduler(){
    sem_post(&mutexS);
}


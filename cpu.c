#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "cpu.h"
struct CPU cpu;
pthread_mutex_t cpu_mutex = PTHREAD_MUTEX_INITIALIZER;
void cpu_inicialize (int coreNum, int hthreadNum){
#ifdef DINIT
	printf("cpu inicialized\n");
#endif
	cpu.coreNum = coreNum;
	cpu.hthreadNum = hthreadNum;
	cpu.cores = calloc(coreNum, sizeof(struct PCB**));
	for(int i = 0; i < coreNum; i++){
		cpu.cores[i] = calloc(cpu.hthreadNum, sizeof(struct PCB*));
	}
}


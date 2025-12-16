#include <stdio.h>
#include <stdlib.h>
#include "prozesuak.h"
#include "cpu.h"
struct CPU cpu;
void cpu_inicialize (int coreNum, int hthreadNum){
	printf("cpu inicialized\n");
	cpu.coreNum = coreNum;
	cpu.hthreadNum = hthreadNum;
	cpu.cores = calloc(coreNum, sizeof(struct PCB**));
	for(int i = 0; i < coreNum; i++){
		cpu.cores[i] = calloc(cpu.hthreadNum, sizeof(struct PCB*));
	}
}


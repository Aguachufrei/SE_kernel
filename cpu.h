#ifndef CPU_H
#define CPU_H
#include <stdio.h>
#include <stdlib.h>
#include "process.h"
extern struct CPU cpu;
extern pthread_mutex_t cpu_mutex;
struct CPU {
	int coreNum;
	int hthreadNum;
	struct PCB ***cores;
};
void cpu_inicialize(int coreNum, int hthreadNum);
#endif

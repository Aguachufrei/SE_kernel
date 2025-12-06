#ifndef CPU_H
#define CPU_H
#include <stdio.h>
#include <stdlib.h>
#include "prozesuak.h"
extern struct CPU cpu;
struct CPU {
	int coreNum;
	int hthreadsNum;
	struct PCB* hthreads;
};
void cpu_inicialize(int core, int hthreads);
#endif

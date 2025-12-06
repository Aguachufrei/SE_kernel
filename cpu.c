#include <stdio.h>
#include <stdlib.h>
#include "prozesuak.h"
#include "cpu.h"
struct CPU cpu;
void cpu_inicialize (int core, int hthreads){
	printf("cpu inicialized\n");
	cpu.coreNum = core;
	cpu.hthreadsNum = hthreads;
	cpu.hthreads = calloc(hthreads, sizeof(struct PCB));
}


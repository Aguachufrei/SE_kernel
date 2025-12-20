#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "memory.h"


uint8_t physical_memory[MEMORY_SIZE];
uint8_t bitmap[PAGE_NUM];


void meminit(){
	memset(bitmap, 1, KERNEL_END_PAGE);
	memset(bitmap + KERNEL_END_PAGE, 0, PAGE_NUM-KERNEL_END_PAGE);
}


int memory_alloc(){
	for(int i = KERNEL_END_PAGE; i<PAGE_NUM; i++){
		if(!bitmap[i]){
			bitmap[i]=1;
			return i;
		}
	}
}


void memory_free(int i){
	if(bitmap[i]){
		bitmap[i]=0;
		return;
	}
	printf("WARNING THIS MEMORY FRAME WAS NEVER ALLOCATED TO BEGIN WITH");
}



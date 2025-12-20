#ifndef MEMORY_H
#define MEMORY_H

#include <string.h> 
#include <stdio.h>
#include <stdint.h>

#define MEMORY_SIZE (1<<24) //2^24, 16MiB 0x000000-0xFFFFFF
#define KERNEL_END_BYTE (1<<22) //2^22, 4MiB, 0x444444
#define PAGE_SIZE 4096 //4KiB
#define PAGE_NUM (MEMORY_SIZE / PAGE_SIZE)
#define KERNEL_END_PAGE (KERNEL_END_BYTE / PAGE_SIZE)

extern uint8_t physical_memory[MEMORY_SIZE]; //Byte
extern uint8_t bitmap[PAGE_NUM]; //Bool 

void meminit();
int memory_alloc();
void memory_free(int page);
struct page_entry {
	uint8_t physical_page;
}
#endif

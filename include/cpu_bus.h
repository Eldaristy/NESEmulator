#ifndef CPU_BUS_H
#define CPU_BUS_H

#include <stdint.h>
#include <assert.h>
#include "ram.h"

//size of each hardware component the cpu bus can access
#define CPU_RAM_SIZE 0x800
#define PPU_REGS_SIZE 0x8
#define APU_IO_REGS_SIZE 0x18
#define DISABLED_APU_IO_SIZE 0x8
#define CARTIDGE_SPACE_SIZE 0xBFE0

//address where each harware component section access starts
#define CPU_RAM_START 0x0
#define PPU_REGS_START 0x2000
#define APU_IO_REGS_START 0x4000
#define DISABLED_APU_IO_START 0x4018
#define CARTIDGE_SPACE_START 0x4020

uint8_t cpu_bus_rd(uint16_t); //read a byte from cpu bus
void cpu_bus_wr(uint16_t, uint8_t); //write a byte to cpu bus

#endif 
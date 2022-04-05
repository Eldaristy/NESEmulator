#ifndef PPU_BUS_H
#define PPU_BUS_H

#include <stdint.h>
#include <assert.h>
#include "ram.h"
#include "ppu.h"

//size of each hardware component the ppu bus can access
#define PATTERN_TABLE_SIZE 0x1000
#define	NAMETABLE_SIZE 0x400
#define PALETTE_RAM_SIZE 0x20

//address where each hardware component section access starts
#define PATTERN_TABLES_START 0x0
#define NAMETABLES_START 0x2000
#define PALETTE_RAM 0x3F00

uint8_t ppu_bus_rd(uint16_t); //read a byte from ppu bus
void ppu_bus_wr(uint16_t, uint8_t); //write a byte to ppu bus

#endif 
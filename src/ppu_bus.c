#include "../include/ppu_bus.h"

uint8_t nametables[NAMETABLE_SIZE * 2] = { 0 };

uint8_t ppu_bus_rd(uint16_t addr)
{
	uint8_t read_data = 0;
	if (addr < NAMETABLES_START) { //pattern tables
		used_mapper.ppu_rd(addr);
	}
	else if (addr < PALETTE_RAM) { //nametables
		used_mapper.ppu_rd(addr);
	}
	else if (addr < 0x4000) { //palette ram
		read_data = palette_ram[addr & 0x1F];
	}
	else { //unaccessable memory
		read_data = 0;
	}
	return read_data;
}
void ppu_bus_wr(uint16_t addr, uint8_t val)
{
	if (addr < NAMETABLES_START) { //pattern tables
		used_mapper.ppu_wr(addr, val);
	}
	else if (addr < PALETTE_RAM) { //nametables
		used_mapper.ppu_wr(addr, val);
	}
	else if (addr < 0x4000) { //palette ram
		palette_ram[addr & 0x1F] = val;
	}
	else { //unaccessable memory
	}
}

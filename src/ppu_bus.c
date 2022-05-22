#include "../include/ppu_bus.h"

uint8_t nametables[NAMETABLE_SIZE * 2] = { 0 };

uint8_t ppu_bus_rd(uint16_t addr)
{
	uint8_t read_data = 0;

	addr = addr & 0x3FFF;

	if (addr < NAMETABLES_START) { //pattern tables
		read_data = used_mapper.ppu_rd(addr);
	}
	else if (addr < PALETTE_RAM) { //nametables
		read_data = used_mapper.ppu_rd(addr);
	}
	else { //palette ram
		//every 4th entry in palette_ram is mapped to the first entry, so:
		if ((addr & 0x13) == 0x10) {
			read_data = palette_ram[0];
		} else { //otherwise read there normally
			read_data = palette_ram[addr & 0x1F];
		}
		
	}
	return read_data;
}
void ppu_bus_wr(uint16_t addr, uint8_t val)
{
	addr = addr & 0x3FFF;

	if (addr < NAMETABLES_START) { //pattern tables
		used_mapper.ppu_wr(addr, val);
	}
	else if (addr < PALETTE_RAM) { //nametables
		used_mapper.ppu_wr(addr, val);
	}
	else { //palette ram
		//exactly like reading palette ram
		if ((addr & 0x13) == 0x10) { 
			palette_ram[0] = val;
		} else {
			palette_ram[addr & 0x1F] = val;
		}
		
	}
}

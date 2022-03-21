#include "../include/cpu_bus.h"

uint8_t cpu_bus_rd(uint16_t addr)
{
	uint8_t read_data = 0;
	if (addr < PPU_REGS_START) { //cpu ram
		read_data = cpu_ram[addr & (CPU_RAM_SIZE - 1)];
	}
	else if (addr < APU_IO_REGS_START) { //ppu registers
		read_data = ppu_regs[addr - PPU_REGS_START];
	} 
	else if (addr < DISABLED_APU_IO_START) { //apu and io registers
		assert(!"not implemented");
	}
	else if (addr < CARTIDGE_SPACE_START) { //disabeld apu and io registers
		assert(!"not implemented");
	}
	else { //cartidge space
		assert(!"not implemented");
	}
	return read_data;
} 
void cpu_bus_wr(uint16_t addr, uint8_t val)
{
	if (addr < PPU_REGS_START) { //cpu ram
		cpu_ram[addr & (CPU_RAM_SIZE - 1)] = val;
	}
	else if (addr < APU_IO_REGS_START) { //ppu registers
		ppu_regs[addr - PPU_REGS_START] = val;
	}
	else if (addr < DISABLED_APU_IO_START) { //apu and io registers
		assert(!"not implemented");
	}
	else if (addr < CARTIDGE_SPACE_START) { //disabeld apu and io registers
		assert(!"not implemented");
	}
	else { //cartidge space
		assert(!"not implemented");
	}
}

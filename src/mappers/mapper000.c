#include "..\..\include\mappers\mapper000.h"

uint8_t cpu_m000_rd(uint16_t addr) 
{
	if (addr >= 0x8000 && addr <= 0xBFFF) {
		return prg_rom_data[addr & 0x3FFF];
	} else {
		return (prg_banks == 1) ? prg_rom_data[addr & 0x3FFF] : prg_rom_data[addr & 0x7FFF];
	}
}
void cpu_m000_wr(uint16_t addr, uint8_t val)
{
	//this mapper maps only to ROM and not RAM inside the cartidge
}
uint8_t ppu_m000_rd(uint16_t addr)
{
	if (addr <= 0x1FFF) {
		return chr_rom_data[addr];
	}
	else {
		return nametables[addr & 0x7FF];
	}
}
void ppu_m000_wr(uint16_t addr, uint8_t val)
{
	if (addr >= 0x2000) {
		nametables[addr & 0x7FF] = val;
	}
}


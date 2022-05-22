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
		addr &= 0xFFF;
		if (flags_6.mirroring == 0) { //HORIZONTAL
			if (addr >= 0 && addr <= 0x3FF) {
				return nametables[addr & 0x3FF];
			} else if (addr >= 0x400 && addr <= 0x7FF) {
				return nametables[addr & 0x3FF];
			} else if (addr >= 0x800 && addr <= 0xBFF){
				return nametables[(addr & 0x3FF) + NAMETABLE_SIZE];
			} else if (addr >= 0xC00 && addr <= 0xFFF) {
				return nametables[(addr & 0x3FF) + NAMETABLE_SIZE];
			}
		}
		else if (flags_6.mirroring == 1) { //VERTICAL
			if (addr >= 0 && addr <= 0x3FF) {
				return nametables[addr & 0x3FF];
			} else if (addr >= 0x400 && addr <= 0x7FF) {
				return nametables[addr & 0x3FF + NAMETABLE_SIZE];
			} else if (addr >= 0x800 && addr <= 0xBFF) {
				return nametables[(addr & 0x3FF)];
			} else if (addr >= 0xC00 && addr <= 0xFFF) {
				return nametables[(addr & 0x3FF) + NAMETABLE_SIZE];
			}
		}
	}
}
void ppu_m000_wr(uint16_t addr, uint8_t val)
{
	if (addr >= 0x2000) {
		addr &= 0xFFF;
		if (flags_6.mirroring == 0) { //HORIZONTAL
			if (addr >= 0 && addr <= 0x3FF) {
				nametables[addr & 0x3FF] = val;
			}
			else if (addr >= 0x400 && addr <= 0x7FF) {
				nametables[addr & 0x3FF] = val;
			}
			else if (addr >= 0x800 && addr <= 0xBFF) {
				nametables[(addr & 0x3FF) + NAMETABLE_SIZE] = val;
			}
			else if (addr >= 0xC00 && addr <= 0xFFF) {
				nametables[(addr & 0x3FF) + NAMETABLE_SIZE] = val;
			}
		}
		else if (flags_6.mirroring == 1) { //VERTICAL
			if (addr >= 0 && addr <= 0x3FF) {
				nametables[addr & 0x3FF] = val;
			}
			else if (addr >= 0x400 && addr <= 0x7FF) {
				nametables[addr & 0x3FF + NAMETABLE_SIZE] = val;
			}
			else if (addr >= 0x800 && addr <= 0xBFF) {
				nametables[(addr & 0x3FF)] = val;
			}
			else if (addr >= 0xC00 && addr <= 0xFFF) {
				nametables[(addr & 0x3FF) + NAMETABLE_SIZE] = val;
			}
		}
	}
}


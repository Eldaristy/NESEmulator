#include "../include/cpu_bus.h"

void gen_nmi() 
{
	assert(!"not implemented");
}

uint8_t cpu_bus_rd(uint16_t addr)
{
	uint8_t read_data = 0;
	if (addr < PPU_REGS_START) { //cpu ram
		read_data = cpu_ram[addr & (CPU_RAM_SIZE - 1)];
	}
	else if (addr < APU_IO_REGS_START) { //ppu registers
		switch (addr) {
		case 0x2000: //PPUCTRL
			read_data = addr_latch;
			break;

		case 0x2001: //PPUMASK
			read_data = addr_latch;
			break;

		case 0x2002: //PPUSTATUS
			read_data = ppustatus.reg;
			ppustatus.vblank = 0;
			addr_latch = 0;
			break;

		case 0x2003: //OAMADDR
			read_data = addr_latch;
			break;

		case 0x2004: //OAMDATA
			read_data = oamdata.reg;
			break;

		case 0x2005: //PPUSCROLL
			read_data = addr_latch;
			break;

		case 0x2006: //PPUADDR
			read_data = addr_latch;
			break;

		case 0x2007: //PPUDATA
			read_data = ppudata.reg;
			vram_addr.reg += ppuctrl.increment_mode ? 32 : 1;
			break;

		case 0x4014: //OAMDMA
			assert(!"not implemented");
		}

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
		switch (addr) {
		case 0x2000: //PPUCTRL
			ppuctrl.reg = val;
			if (ppustatus.vblank) {
				gen_nmi();
			}

			temp_vram_addr.nametable = ppuctrl.nametable_y << 1 | ppuctrl.nametable_x;
			break;

		case 0x2001: //PPUMASK
			ppumask.reg = val;
			break;

		case 0x2002: //PPUSTATUS
			break;

		case 0x2003: //OAMADDR
			oamaddr.reg = val;
			break;

		case 0x2004: //OAMDATA
			oamdata.reg = val;
			break;

		case 0x2005: //PPUSCROLL
			ppuscroll.reg = val;

			if (addr_latch == 0) {
				temp_vram_addr.coarse_x = val >> 3; //5 higher bits
				fine_x_scroll = val & 0x07; //3 lower bits
				addr_latch = 1;
			}
			else { //addr_latch == 1
				temp_vram_addr.coarse_y = val >> 3;
				temp_vram_addr.fine_y_scroll = val & 0x07;
				addr_latch = 0;
			}
			break;

		case 0x2006: //PPUADDR
			ppuaddr.reg = val;

			if (addr_latch == 0) {
				temp_vram_addr.reg &= val << 8 | 0xFF; 
				temp_vram_addr.reg &= 0x3FFF; // clear highest 2 bits
				addr_latch = 1;
			}
			else { //addr_latch == 1
				temp_vram_addr.reg &= val | 0x3F00;
				vram_addr.reg = temp_vram_addr.reg;
				addr_latch = 0;
			}
			break;

		case 0x2007: //PPUDATA
			ppu_bus_wr(vram_addr.reg, val);
			vram_addr.reg += (ppuctrl.increment_mode ? 32 : 1);
			break;

		case 0x4014: //OAMDMA
			assert(!"not implemented");
		}
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

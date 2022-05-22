#include "../include/cpu_bus.h"

uint8_t cpu_ram[CPU_RAM_SIZE] = { 0 };

uint8_t cpu_bus_rd(uint16_t addr)
{
	uint8_t read_data = 0;
	if (addr < PPU_REGS_START) { //cpu ram
		read_data = cpu_ram[addr & (CPU_RAM_SIZE - 1)];
	}
	else if (addr < APU_REGS_START) { //ppu and apu registers
		switch (addr & 0x07) {
		case 0x00: //PPUCTRL
			read_data = addr_latch;
			break;

		case 0x01: //PPUMASK
			read_data = addr_latch;
			break;

		case 0x02: //PPUSTATUS
			read_data = ppustatus.reg;
			ppustatus.vblank = 0;
			ppustatus.spr_zero = 0;
			addr_latch = 0;
			break;

		case 0x03: //OAMADDR
			read_data = addr_latch;
			break;

		case 0x04: //OAMDATA
			read_data = oamdata.reg;
			break;

		case 0x05: //PPUSCROLL
			read_data = addr_latch;
			break;

		case 0x06: //PPUADDR
			read_data = addr_latch;
			break;

		case 0x07: //PPUDATA
			read_data = ppu_data_buffer;
			ppu_data_buffer = ppu_bus_rd(vram_addr.reg);
			if (vram_addr.reg >= 0x3F00) {
				read_data = ppu_data_buffer;
			}
			vram_addr.reg += ppuctrl.increment_mode ? 32 : 1;
			break;

		}

	} else if (addr < DISABLED_APU_START) {
		read_data = apu_temp[addr & 0x1F];
		if (addr == 0x4016) {
			if (strobe == 0) {
				//read the first bit which is the "current" button being checked
				read_data = controller_shift_reg & 0x01;

				//shift the control register to the right so next read it will read the next button
				controller_shift_reg >>= 1;
			}
		}
	}
	
	else if (addr < CARTIDGE_SPACE_START) { //disabled apu and io registers
		assert(!"not implemented");
	}
	else { //cartidge space
		read_data = used_mapper.cpu_rd(addr);
	}
	return read_data;
} 
void cpu_bus_wr(uint16_t addr, uint8_t val)
{
	if (addr < PPU_REGS_START) { //cpu ram
		cpu_ram[addr & (CPU_RAM_SIZE - 1)] = val;
	} else if (addr < APU_REGS_START) { //ppu and apu registers
		switch (addr & 0x07) {
		case 0x00: //PPUCTRL
			ppuctrl.reg = val;
			if (ppustatus.vblank) {
				if (ppuctrl.gen_nmi) {
					//gen_nmi();
				}
			}

			temp_vram_addr.nametable_x = ppuctrl.nametable_x;
			temp_vram_addr.nametable_y = ppuctrl.nametable_y;
			break;

		case 0x01: //PPUMASK
			ppumask.reg = val;
			break;

		case 0x02: //PPUSTATUS
			break;

		case 0x03: //OAMADDR
			oamaddr.reg = val;
			break;

		case 0x04: //OAMDATA
			oamdata.reg = val;
			((uint8_t*)primary_oam)[oamaddr.reg] = oamdata.reg;
			break;

		case 0x05: //PPUSCROLL
			ppuscroll.reg = val;

			if (addr_latch == 0) {
				//1st time: fill in the fine/coarse x components to temp_vram_addr
				temp_vram_addr.coarse_x = val >> 3; //5 higher bits
				fine_x_scroll = val & 0x07; //3 lower bits
				addr_latch = 1;
			} else { //addr_latch == 1
				//2nd time: fill in the fine/coarse y components to temp_vram_addr
				temp_vram_addr.coarse_y = val >> 3;
				temp_vram_addr.fine_y_scroll = val & 0x07;
				addr_latch = 0;
			}
			break;

		case 0x06: //PPUADDR
			ppuaddr.reg = val;

			//different way of filling temp_vram_addr:
			if (addr_latch == 0) {
				//1st time: fill in the upper 8 bits into temp_vram_addr (highest 2 are discarded)
				temp_vram_addr.reg = (val << 8) | 0xFF;
				temp_vram_addr.reg &= 0x3FFF; // clear highest 2 bits
				addr_latch = 1;
			}
			else { //addr_latch == 1
				//2nd time: fill in the lower 8 bits into temp_vram_addr
				//AND assign vram_addr value to be like temp_vram_addr
				temp_vram_addr.reg &= val | 0x3F00;
				vram_addr.reg = temp_vram_addr.reg;
				addr_latch = 0;
			}
			break;

		case 0x07: //PPUDATA
			ppu_bus_wr(vram_addr.reg, val);
			vram_addr.reg += (ppuctrl.increment_mode ? 32 : 1);
			break;

		}
	} else if (addr < DISABLED_APU_START) {
		apu_temp[addr & 0x1F] = val;
		if (addr == 0x4014) { //OAMDMA
			oamdma.reg = val;
			for (uint16_t i = 0; i < 0x100; i++) {
				((uint8_t*)primary_oam)[i] = cpu_bus_rd(((uint16_t)(oamdma.reg) << 8) + i);
			}
		} else if (addr == 0x4016) { //controller register
			strobe = val & 0x01;
			if (strobe == 1) {
				//load the controller's shift register
				controller_shift_reg = buttons.all_buttons;
			} 
		}
	} else if (addr < CARTIDGE_SPACE_START) { //oamdma, disabled apu and io registers
		assert("not implemented");
	} else { //cartidge space
		used_mapper.cpu_wr(addr, val);
	}
}

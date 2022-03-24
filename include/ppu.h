#ifndef PPU_H
#define PPU_H

#include <stdint.h>
#include "ppu_bus.h"

//ppu registers
//#define PPUCTRL 0x2000;
//#define PPUMASK 0x2001;
//#define PPUSTATUS 0x2002;
//#define OAMADDR 0x2003;
//#define OAMDATA 0x2004;
//#define PPUSCROLL 0x2005;
//#define PPUADDR 0x2006;
//#define PPUDATA 0x2007;
//#define OAMDMA 0x4014;

//PPU internal registers - "Loopy" registers

//vram_addr and temp_vram_addr - 15 bits long
union {
	struct {
		uint16_t coarse_x : 5;
		uint16_t coarse_y : 5;
		uint16_t nametable : 2;
		uint16_t fine_y_scroll : 3;
		// LAST BIT IS UNUSED
	};
	uint16_t reg;
} vram_addr, temp_vram_addr;

uint8_t fine_x_scroll; //3 bits long
uint8_t addr_latch; //1 bit long

union PPUCTRL{ //Access: write
	struct {
		uint8_t nametable_x : 1;
		uint8_t nametable_y : 1;
		uint8_t increment_mode : 1;
		uint8_t spr_patterntable : 1;
		uint8_t bkg_nametable_y : 1;
		uint8_t spr_size : 1;
		uint8_t master_slave : 1;
		uint8_t gen_nmi : 1;
	};
	uint8_t reg;
} ppuctrl;

union PPUMASK { //Access: write
	struct {
		uint8_t greyscale : 1;
		uint8_t show_bkg_left : 1;
		uint8_t show_spr_left : 1;
		uint8_t show_bkg : 1;
		uint8_t show_spr : 1;
		uint8_t emph_red : 1;
		uint8_t emph_green : 1;
		uint8_t emph_blue : 1;
	};
	uint8_t reg;
} ppumask;

union PPUSTATUS { //Access: read
	struct {
		uint8_t UNUSED: 5;
		uint8_t spr_overflow: 1;
		uint8_t spr_zero: 1;
		uint8_t vblank: 1;
	};
	uint8_t reg;
} ppustatus;

union OAMADDR{ //Access: write
	uint8_t reg;
} oamaddr;

union OAMDATA { //Access: read, write
	uint8_t reg;
} oamdata;

union PPUSCROLL { //Access: write x2
	uint8_t reg;
} ppuscroll;

union PPUADDR { //Access: write x2
	uint8_t reg;
} ppuaddr;

union PPUDATA { //Access: write x2
		uint8_t reg;
} ppudata;

void gen_nmi();
#endif

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

uint8_t oam[0x100];

static uint8_t pattern_tables[0x1000][2];

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

//shift registers used for background rendering:
static uint16_t patt_tbl_data[2];
static uint8_t pall_attr_data[2];

//shift registers used for sprite rendering:


union PPUCTRL{ //Access: write
	struct {
		uint8_t nametable_x : 1;
		uint8_t nametable_y : 1;
		uint8_t increment_mode : 1;
		uint8_t spr_pattern_table : 1;
		uint8_t bkg_pattern_table : 1;
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

union OAMDMA { //Access: write 
	uint8_t reg;
} oamdma;

void gen_nmi();
void cycle();

//all scanline stages:
void pre_render();
void render();
void post_render();
void vertical_blank();

//all rendering stages (cycles inside render()):
//"void idle()"
void fetch_data();
void evaluate_sprites(); //a process which is taken beside the one of fetch_data()
void fetch_next_scl_sprites();
void fetch_next_scl_tiles();
//"void do_nothing()"

static uint16_t dot;
static uint16_t scanlines;

//latches used when fetching data for background rendering
static uint8_t patt_tbl_id;
static uint8_t attr_tbl_id;
static uint8_t patt_tbl_lo;
static uint8_t patt_tbl_hi;

//background shift registers
static uint16_t bkg_patt_shift[2];
static uint8_t bkg_attr_shift[2];

//sprite shift registers


#define IDLE_CYCLE (dot == 0)
#define VISIBLE_CYCLE (dot >= 1 && dot <= 256)
#define INVISIBLE_CYCLE (dot > 257 && dot <= 320)

#define PRE_RENDER_SCL (scanlines == -1)


#endif

#ifndef PPU_H
#define PPU_H

#include <stdint.h>
#include "ppu_bus.h"
#include "cpu.h"
#include "../include/display.h"	

uint8_t colors[0x48][3];

//typedef uint32_t palette;
uint8_t palette_ram[0x20];

void ppu_init();

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

union OAMADDR { //Access: write
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
void ppu_clock();

//all scanline stages:
void pre_render();
void render();
void post_render();
void vertical_blank();

void load_bkg_shifts();

void reverse_bits(uint8_t*); //helper function to reverse bits of an 8-bit word

//all rendering stages (cycles inside render()):
//"void idle()"
void fetch_next_scl_bkground();
void evaluate_sprites(); //a process which is taken beside the one of fetch_next_scl_bkground()
void fetch_next_scl_sprites();

void create_pixel();

uint16_t dot;
int16_t scanline;

//PPU internal registers - AKA "Loopy" registers:
//vram_addr and temp_vram_addr - 15 bits long
union {
	struct {
		uint16_t coarse_x : 5;
		uint16_t coarse_y : 5;
		uint16_t nametable_x : 1;
		uint16_t nametable_y : 1;
		uint16_t fine_y_scroll : 3;
		// LAST BIT IS UNUSED
	};
	uint16_t reg;
} vram_addr, temp_vram_addr;
uint8_t fine_x_scroll; //3 bits long
uint8_t addr_latch; //1 bit long
//background shift registers
uint16_t bkg_patt_shift_lo;
uint16_t bkg_patt_shift_hi;
uint8_t bkg_attr_shift_lo;
uint8_t bkg_attr_shift_hi;
//latches used when fetching data for background rendering
uint8_t patt_tbl_id;
uint8_t attr_tbl_id;
uint8_t patt_tbl_lo;
uint8_t patt_tbl_hi;

uint8_t current_attr_tbl_id;

typedef union {
	struct {
		uint8_t palette : 2;
		uint8_t UNUSED : 3;
		uint8_t priority : 1;
		uint8_t flip_horizon : 1;
		uint8_t flip_vertical : 1;
	};
	uint8_t reg;
} spr_attr;
typedef struct {
	uint8_t y_top;
	uint8_t tile_index;
	spr_attr attr;
	uint8_t x_left;
} sprite;
//memory used for storing sprites
sprite primary_oam[64]; //oam exposed to the cpu via OAMADDR, OAMDATA and OAMDMA registers
sprite secondary_oam[8]; //short-term oam
uint16_t primary_oam_counter; //referred to "n" in NESdev
uint16_t secondary_oam_counter; 
uint8_t oam_temp;
//latches used when fetching data for foreground (sprite) rendering
spr_attr spr_attrs[8];
uint8_t spr_counters[8];
//sprite shift registers
uint8_t spr_patt_shift_lo[8];
uint8_t spr_patt_shift_hi[8];

uint8_t current_spr_index;
uint8_t spr_zero_might_hit;
uint8_t is_spr_zero_rendered;

#endif

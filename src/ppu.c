#include "../include/ppu.h"

static uint8_t pattern_tables[0x1000][2] = {0};

uint8_t pallete[0x40][3] = {
	{84, 84, 84},
	{0, 30, 116},
	{8, 16, 144},
	{48, 0, 136},
	{68, 0, 100},
	{92, 0, 48},
	{84, 4, 0},
	{60, 24, 0},
	{32, 42, 0},
	{8, 58, 0},
	{0, 64, 0},
	{0, 60, 0},
	{0, 50, 60},
	{0, 0, 0},
	{152, 150, 152},
	{8, 76, 196},
	{48, 50, 236},
	{92, 30, 228},
	{136, 20, 176},
	{160, 20, 100},
	{152, 34, 32},
	{120, 60, 0},
	{84, 90, 0},
	{40, 114, 0},
	{8, 124, 0},
	{0, 118, 40},
	{0, 102, 120},
	{0, 0, 0},
	{236, 238, 236},
	{76, 154, 236},
	{120, 124, 236},
	{176, 98, 236},
	{228, 84, 236},
	{236, 88, 180},
	{236, 106, 100},
	{212, 136, 32},
	{160, 170, 0},
	{116, 196, 0},
	{76, 208, 32},
	{56, 204, 108},
	{56, 180, 204},
	{60, 60, 60},
	{236, 238, 236},
	{168, 204, 236},
	{188, 188, 236},
	{212, 178, 236},
	{236, 174, 236},
	{236, 174, 212},
	{236, 180, 176},
	{228, 196, 144},
	{204, 210, 120},
	{180, 222, 120},
	{168, 226, 144},
	{152, 226, 180},
	{160, 214, 228},
	{160, 162, 160},
};

void render()
{
	if (dot == 0) {
		//idle cycle
	} else if (dot <= 256) {
		//render cycle
		switch (dot - 1 % 8) {
			case 0:
				//fetch pattern table byte
				patt_tbl_id = ppu_bus_rd(NAMETABLES_START
					| (vram_addr.reg & 0x0FFF));
				break;

			case 2:
				//fetch attribute table byte
				attr_tbl_id = ppu_bus_rd(NAMETABLES_START
					| (NAMETABLE_SIZE - 0x40)
					| (vram_addr.nametable << 11)
					| (vram_addr.coarse_y >> 2 << 3)
					| (vram_addr.coarse_x >> 2));
				break;

			case 4:
				patt_tbl_lo = ppu_bus_rd(ppuctrl.bkg_pattern_table << 12
					| (uint16_t)patt_tbl_id << 4
					| vram_addr.fine_y_scroll);
				break;

			case 6:
				patt_tbl_hi = ppu_bus_rd(ppuctrl.bkg_pattern_table << 12
					| (uint16_t)patt_tbl_id << 4
					| vram_addr.fine_y_scroll + 8);
				break;

			case 7:
				//increment fine_x_scroll, then check if it wraps around and requires
				//incrementing coarse_x... then nametable...
				fine_x_scroll++;
				if (fine_x_scroll == 8) {
					fine_x_scroll = 0;
					vram_addr.coarse_x++;
				}
				if (vram_addr.coarse_x == 31) {
					vram_addr.coarse_x = 0;
					vram_addr.nametable++;
				}
				if (vram_addr.nametable == 3) {
					vram_addr.nametable = 0;
				}
				fine_x_scroll = (fine_x_scroll == 8) ? 0 : fine_x_scroll;
		}
			

		
	} else if (dot <= 320) {
		//fetch data for sprites in next scanline
	}
	else if (dot <= 336) {
		//fetch data for first 2 tiles in next scanline
	}
	else {
		//do nothing
	}
	dot++;
	dot = (dot == 341) ? 0 : dot;
}

void cycle()
{
	if (scanlines == -1) {
		//dummy
	}
	else if (scanlines <= 239) {
		//visible scanlines
		render();
	}
	else if (scanlines == 240) {
		//post-render
	}
	else { // 241-260
		//vertical blank
	}
	scanlines++;
	scanlines = (scanlines == 261) ? -1 : scanlines;
}


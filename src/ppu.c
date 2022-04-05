#include "../include/ppu.h"

static uint8_t pattern_tables[0x1000][2] = {0};

uint8_t colors[0x40][3] = {
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

void load_bkg_shifts()
{
	uint8_t mod_coarse_x = vram_addr.coarse_x % 4;
	uint8_t mod_coarse_y = vram_addr.coarse_y % 4;
	
	bkg_patt_shift_lo = bkg_patt_shift_lo & 0xFF | (uint16_t)(patt_tbl_lo) << 8;
	bkg_patt_shift_hi = bkg_patt_shift_hi & 0xFF | (uint16_t)(patt_tbl_hi) << 8;

	if (mod_coarse_y <= 1) { //top
		if (mod_coarse_x <= 1) { //top-left
			bkg_attr_shift_lo = attr_tbl_id & 0x01;
			bkg_attr_shift_hi = attr_tbl_id & 0x02;
		} else { //top-right
			bkg_attr_shift_lo = attr_tbl_id & 0x04;
			bkg_attr_shift_hi = attr_tbl_id & 0x08;
		}
	} else { //bottom
		if (mod_coarse_x <= 1) { //bottom-left
			bkg_attr_shift_lo = attr_tbl_id & 0x10;
			bkg_attr_shift_hi = attr_tbl_id & 0x20;
		}
		else { //bottom-right
			bkg_attr_shift_lo = attr_tbl_id & 0x40;
			bkg_attr_shift_hi = attr_tbl_id & 0x80;
		}
	}
}
void load_spr_shifts()
{

}

void pre_render()
{

}

void fetch_next_scl_bkground()
{
	switch (dot - 1 % 8) {
	case 0:
		load_bkg_shifts();

		//fetch pattern table byte
		patt_tbl_id = ppu_bus_rd(NAMETABLES_START
			| (vram_addr.reg & 0x0FFF));
		break;

	case 2:
		//fetch attribute table byte
		attr_tbl_id = ppu_bus_rd(NAMETABLES_START
			| (NAMETABLE_SIZE - 0x40)
			| (vram_addr.nametable << 11)
			| ((vram_addr.coarse_y >> 2) << 3)
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
		break;
	}
}
void evaluate_sprites()
{
	if (dot >= 1 && dot <= 64) {
		oam_counter = 0;
		for (uint8_t i = 0; i < 8; i++) {
			secondary_oam[i] = (sprite){ 0xFF, 0xFF, 0xFF, 0xFF };
		}
	} else if (dot <= 256) {
		switch (dot % 2) {
		case 1:
			oam_temp = primary_oam[oam_counter];
			break;
		
		case 0:
			if (oam_counter < 8) {
				secondary_oam[oam_counter] = oam_temp; //here I simplified a little bit...
				//instead of copying just the first byte of the sprite then check if I
				//have to copy all the rest and increment oam_counter, I decided to
				//copy all 4 bytes from the start and decide whether or not to increment oam_counter
				
			} else {
				oam_temp = secondary_oam[7];
			}
		}
	} else if (dot <= 320) {
		oam_counter = 0;
	}
}
void create_pixel()
{
	uint8_t bkg_pixel = 0;
	palette bkg_palette = 0;
	uint8_t spr_pixel = 0; 
	palette spr_palette = 0;
	uint8_t final_pixel = 0;
	palette final_palette = 0;

	bkg_pixel = (bkg_patt_shift_lo & 0x0001) | (bkg_patt_shift_hi & 0x0001 << 1);
	bkg_palette = (bkg_attr_shift_lo & 0x01) | (bkg_attr_shift_hi & 0x01 << 1);
	bkg_palette = palette_ram[bkg_palette];
	
	spr_pixel = 0; //not implemented yet...
	spr_palette = palette_ram[secondary_oam[current_spr_index].attr.palette + 4];

	if (bkg_pixel == 0 && spr_pixel == 0) {
		final_pixel = bkg_pixel;
		//final_palette doesn't matter because it's background color anyways
	} else if (bkg_pixel == 0 && spr_pixel > 0) {
		final_pixel = spr_pixel;
		final_palette = spr_palette;
	} else if (bkg_pixel > 0 && spr_pixel == 0) {
		final_pixel = bkg_pixel;
		final_palette = bkg_palette;
	} else {
		if (secondary_oam[current_spr_index].attr.priority) {
			final_pixel = bkg_pixel;
			final_palette = bkg_palette;
		} else {
			final_pixel = spr_pixel;
			final_palette = spr_palette;
		}
	}

	set_pixel(dot - 1, scanline, colors[((uint8_t*)palette_ram)[final_palette * 4 + final_pixel]]);
}
void fetch_next_scl_sprites()
{
	//here the structure is very similar to the one of fetch_next_scl_bkground(), but even simpler
	switch (dot - 1 % 8) {
	case 0:
		load_spr_shifts();

		//fetch garbage data
		break;

	case 2:
		//fetch garbage data
		break;

	case 4:
		spr_patt_shift_lo[oam_counter] = ppu_bus_rd(ppuctrl.spr_pattern_table << 12
			| (uint16_t)(secondary_oam[oam_counter].tile_index) << 4
			| scanline - secondary_oam[oam_counter].y_top);
		break;

	case 6:
		spr_patt_shift_lo[oam_counter] = ppu_bus_rd(ppuctrl.spr_pattern_table << 12
			| (uint16_t)(secondary_oam[oam_counter].tile_index) << 4
			| scanline - secondary_oam[oam_counter].y_top + 8);
		break;
	}
}
void render()
{
	if (dot == 0) {
		//idle cycle
	} else if (dot <= 256) {
		//render cycle
		fetch_next_scl_bkground();
		create_pixel();

		//now for the reason they are called SHIFT registers...
		bkg_patt_shift_lo >>= 1;
		bkg_patt_shift_hi >>= 1;
	} else if (dot <= 320) {
		//fetch data for sprites in next scanline
		fetch_next_scl_sprites();
	} else if (dot <= 336) {
		//fetch data for first 2 tiles in next scanline
		fetch_next_scl_bkground();

		bkg_patt_shift_lo >>= 1;
		bkg_patt_shift_hi >>= 1;
	} else {
		//do nothing (purpose of cycles 337-340 are unknown and probably not impactful)
	}

	

	dot++;
	dot = (dot == 341) ? 0 : dot;
}

void post_render()
{

}

void vertical_blank()
{

}

void cycle()
{
	if (scanline == -1) {
		//dummy
		pre_render();
	}
	else if (scanline <= 239) {
		//visible scanline
		evaluate_sprites();
		render();
	}
	else if (scanline == 240) {
		//post-render
		post_render();
	}
	else { // 241-260
		//vertical blank
		vertical_blank();
	}
	scanline++;
	scanline = (scanline == 261) ? -1 : scanline;
}


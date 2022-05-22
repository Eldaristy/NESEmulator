#include "../include/ppu.h"

uint8_t colors[0x48][3] = {
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
	{0, 0, 0},
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
	{0, 0, 0},
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
	{0, 0, 0},
	{0, 0, 0},
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
	{0, 0, 0},
	{0, 0, 0},
};

void gen_nmi()
{
	nmi_line = 1;
}

void ppu_init()
{
	ppuctrl.reg = 0;
	ppumask.reg = 0;
	ppustatus.reg = 0;
	oamaddr.reg = 0;
	oamdata.reg = 0;
	ppuscroll.reg = 0;
	ppuaddr.reg = 0;
	ppudata.reg = 0;
	oamdma.reg = 0;

	dot = 0;
	scanline = -1;

	vram_addr.reg = 0;
	temp_vram_addr.reg = 0;
	fine_x_scroll = 0;
	addr_latch = 0;

	bkg_patt_shift_lo = 0;
	bkg_patt_shift_hi = 0;
	bkg_attr_shift_lo = 0;
	bkg_attr_shift_hi = 0;

	patt_tbl_id = 0;
	attr_tbl_id = 0;
	patt_tbl_lo = 0;
	patt_tbl_hi = 0;
}

void load_bkg_shifts()
{
	uint8_t mod_coarse_x = (vram_addr.coarse_x - 2) & 3; //same as "% 2", just wanted to use bit-wise
	uint8_t mod_coarse_y = vram_addr.coarse_y & 3;

	reverse_bits(&patt_tbl_lo);
	reverse_bits(&patt_tbl_hi);

	bkg_patt_shift_lo = (bkg_patt_shift_lo & 0xFF) | ((uint16_t)(patt_tbl_lo) << 8);
	bkg_patt_shift_hi = (bkg_patt_shift_hi & 0xFF) | ((uint16_t)(patt_tbl_hi) << 8);

	if (mod_coarse_y == 0 || mod_coarse_y == 1) { //top
		if (mod_coarse_x == 0 || mod_coarse_x == 1) { //top-left
			bkg_attr_shift_lo = attr_tbl_id & 0x01;
			bkg_attr_shift_hi = (attr_tbl_id & 0x02) >> 1;
		} else { //top-right
			bkg_attr_shift_lo = (attr_tbl_id & 0x04) >> 2;
			bkg_attr_shift_hi = (attr_tbl_id & 0x08) >> 3;
		}
	} else { //bottom
		if (mod_coarse_x == 0 || mod_coarse_x == 1) { //bottom-left
			bkg_attr_shift_lo = (attr_tbl_id & 0x10) >> 4;
			bkg_attr_shift_hi = (attr_tbl_id & 0x20) >> 5;
		}
		else { //bottom-right
			bkg_attr_shift_lo = (attr_tbl_id & 0x40) >> 6;
			bkg_attr_shift_hi = (attr_tbl_id & 0x80) >> 7;
		}
	}
	if (bkg_attr_shift_lo) {
		bkg_attr_shift_lo = 0xFF;
	}
	if (bkg_attr_shift_hi) {
		bkg_attr_shift_hi = 0xFF;
	}
}

//that's a nice one... reversing the bits is essential since we use the low bits of the shift registers
//to draw the pixels each time (and then shift them right).
void reverse_bits(uint8_t* pointer)
{
	*pointer = (*pointer & 0x7E) | ((*pointer & 0x80) >> 7) | ((*pointer & 0x01) << 7);
	*pointer = (*pointer & 0xBD) | ((*pointer & 0x40) >> 5) | ((*pointer & 0x02) << 5); 
	*pointer = (*pointer & 0xDB) | ((*pointer & 0x20) >> 3) | ((*pointer & 0x04) << 3); 
	*pointer = (*pointer & 0xE7) | ((*pointer & 0x10) >> 1) | ((*pointer & 0x08) << 1);
}

void pre_render()
{
	if (dot == 0) {
		ppustatus.vblank = 0;
	} else if (dot == 1) {
		ppustatus.spr_overflow = 0;
		ppustatus.spr_zero = 0;
		spr_zero_might_hit = true;
		for (uint8_t i = 0; i < 8; i++) {
			spr_patt_shift_lo[i] = 0;
			spr_patt_shift_hi[i] = 0;
		}
	} else if (dot == 280) {
		if (ppumask.show_bkg || ppumask.show_spr) {
			vram_addr.coarse_y = temp_vram_addr.coarse_y;
			vram_addr.nametable_y = temp_vram_addr.nametable_y;
			vram_addr.fine_y_scroll = temp_vram_addr.fine_y_scroll;
		}
	} else if (dot >= 321 && dot <= 336) {
	//fetch data for first 2 tiles in next scanline
		fetch_next_scl_bkground();

		bkg_patt_shift_lo >>= 1;
		bkg_patt_shift_hi >>= 1;
	} 
}

void fetch_next_scl_bkground()
{
	switch ((dot - 1) & 0x07) {
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
			| ((vram_addr.nametable_x | (vram_addr.nametable_y << 1)) << 11)
			| ((vram_addr.coarse_y >> 2) << 3)
			| ((vram_addr.coarse_x - 1) >> 2));

		break;

	case 4:
		patt_tbl_lo = ppu_bus_rd((ppuctrl.bkg_pattern_table << 12)
			| ((uint16_t)patt_tbl_id << 4)
			| vram_addr.fine_y_scroll);
		break;

	case 6:
		patt_tbl_hi = ppu_bus_rd((ppuctrl.bkg_pattern_table << 12)
			| ((uint16_t)patt_tbl_id << 4)
			| (vram_addr.fine_y_scroll + 8));
		break;

	case 7:
		if (dot >= 249 && dot <= 256) { //if we are in the last background tile of the scanline
			return; //don't do anything with the fetch
		}
		if (ppumask.show_bkg || ppumask.show_spr) {
			if (vram_addr.coarse_x == 31) {
				vram_addr.coarse_x = 0;
				vram_addr.nametable_x = ~vram_addr.nametable_x;
			}
			else {
				vram_addr.coarse_x++;
			}
		}
		
		break;
	}
}
void evaluate_sprites()
{
	int16_t diff = 0;
	primary_oam_counter = 0;
	secondary_oam_counter = 0;
	if (scanline == 176) {
		scanline = scanline;
	}
	for (uint8_t i = 0; i < 8; i++) {
		memset(&(secondary_oam[i]), 0xFFFFFFFF, sizeof(uint8_t) * 4);
	}

	while (primary_oam_counter / 4 < 64 && secondary_oam_counter / 4 < 9) {
		((uint8_t*)secondary_oam)[secondary_oam_counter] = ((uint8_t*)primary_oam)[primary_oam_counter];
		diff = scanline + 1 - ((int16_t)(secondary_oam[secondary_oam_counter / 4].y_top));
		if (scanline == 0xcd) {
			diff = diff;
		}
		if (scanline == 0xce) {
			diff = diff;
		}
		if ((diff >= 0 && diff <= 7 && !ppuctrl.spr_size)
			| (diff >= 0 && diff <= 15 && ppuctrl.spr_size)) {
			if (secondary_oam_counter < 32) {
				
				secondary_oam[secondary_oam_counter / 4] = primary_oam[primary_oam_counter / 4];
				//secondary_oam[secondary_oam_counter / 4].y_top++;
				secondary_oam_counter += 4;
				ppustatus.spr_overflow = 0;
			} else {
				ppustatus.spr_overflow = 1;
			}
		}

		primary_oam_counter += 4;
		
	}
}
void create_pixel()
{
	uint8_t bkg_pixel = 0;
	uint8_t bkg_palette = 0;
	uint8_t bkg_scroll_mask = 0;
	uint8_t spr_pixel = 0; 
	uint8_t spr_palette = 0;
	uint8_t final_pixel = 0;
	uint8_t final_palette = 0;
	uint8_t color[3] = { 0 };

	bkg_scroll_mask = 0x0001 << fine_x_scroll;
	if (dot == 0x59) {
		dot = dot;
	}
	if (ppumask.show_bkg) {
		bkg_pixel = ((bkg_patt_shift_lo & bkg_scroll_mask) > 0) | (((bkg_patt_shift_hi & bkg_scroll_mask) > 0) << 1);
		bkg_palette = (bkg_attr_shift_lo & 0x01) | ((bkg_attr_shift_hi & 0x01) << 1); 
	}

	for (uint8_t i = 0; i < 8; i++) {	
		if (
			secondary_oam[i].y_top < 240
			&& (uint8_t)(dot - 1) - (uint8_t)(secondary_oam[i].x_left) >= 0
			&& (uint8_t)(dot - 1) - (uint8_t)(secondary_oam[i].x_left) <= 7) {// IMPORTANT: IN BALLOON FIGHT: && secondary_oam[i].y_top != 0xf0) {
			spr_pixel = (spr_patt_shift_lo[i] & 0x01) | ((spr_patt_shift_hi[i] & 0x01) << 1);
			spr_patt_shift_lo[i] >>= 1;
			spr_patt_shift_hi[i] >>= 1;

			if (i == 0 && spr_zero_might_hit
				&& spr_pixel != 0 && bkg_pixel != 0
				&& ppumask.show_bkg && ppumask.show_spr) {
				is_spr_zero_rendered = true;
				if (!(ppumask.show_bkg_left || ppumask.show_spr_left) && is_spr_zero_rendered) {
					if (dot >= 9 && dot < 258) {
						spr_zero_might_hit = false;
 						ppustatus.spr_zero = 1;
					}
				} else if(is_spr_zero_rendered){
					if (dot >= 1 && dot < 258) {
						spr_zero_might_hit = false;
						ppustatus.spr_zero = 1;
					}
				}
				
			}
			break;
		} 
	}

	spr_palette = secondary_oam[current_spr_index].attr.palette + 4;

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

	if (final_pixel == 0) {
		final_palette = 0;
	}
	memcpy(color, colors[palette_ram[final_palette * 4 + final_pixel]], 3 * sizeof(uint8_t));
	al_draw_pixel(dot, scanline + 1, al_map_rgb(color[0], color[1], color[2]));
	if (dot == 256 && scanline == 239) {
		al_set_target_backbuffer(display);
		al_draw_scaled_bitmap(bitmap, 0, 0, 256, 240, 0, 0, 256 * WINDOW_SCALE, 240 * WINDOW_SCALE, NULL);
		al_flip_display();
		al_set_target_bitmap(bitmap);
		run_controller();
	}
}
void fetch_next_scl_sprites()
{
	uint8_t temp = 0;
	//here the structure is very similar to the one of fetch_next_scl_bkground(), but even simpler
	switch ((dot - 1) & 0x07) {
	case 0:
		is_spr_zero_rendered = false;
		//fetch garbage data
		break; 

	case 2:
		//fetch garbage data
		break;

	case 4:
		temp = scanline + 1 - secondary_oam[secondary_oam_counter / 4].y_top;
		if (scanline == 0xb0) {
			scanline = scanline;
		}
		switch (temp) {
		case 1:
			temp = temp;
			break;
		case 2:
			temp = temp;
			break;
		case 3:
			temp = temp;
			break;
		case 4:
			temp = temp;
			break;
		case 5:
			temp = temp;
			break;
		case 6:
			temp = temp;
			break;
		case 7:
			temp = temp;
			break;
		case 8:
			temp = temp;
			break;
		} 

		spr_patt_shift_lo[secondary_oam_counter / 4] = ppu_bus_rd((ppuctrl.spr_pattern_table << 12)
			| (secondary_oam[secondary_oam_counter / 4].tile_index << 4)
			| (((scanline - secondary_oam[secondary_oam_counter / 4].y_top) & 0x07)));
		if (!(secondary_oam[secondary_oam_counter / 4].attr.reg & 0x40)) {
			reverse_bits(&(spr_patt_shift_lo[secondary_oam_counter / 4]));
		}
		
		break;

	case 6:
		spr_patt_shift_hi[secondary_oam_counter / 4] = ppu_bus_rd((ppuctrl.spr_pattern_table << 12)
			| (secondary_oam[secondary_oam_counter / 4].tile_index << 4)
			| (((scanline - secondary_oam[secondary_oam_counter / 4].y_top) & 0x07) + 8));
		if (!(secondary_oam[secondary_oam_counter / 4].attr.reg & 0x40)) {
			reverse_bits(&(spr_patt_shift_hi[secondary_oam_counter / 4]));
		}

		secondary_oam_counter += 4;
		break;
	}
}
void render()
{
	if (dot == 0) {
		//idle cycle, but lets just put the sprite evaluation in one hit there...
		
		secondary_oam_counter = 0;
	} else if (dot <= 256) {
		//render cycle
		fetch_next_scl_bkground();
		create_pixel();
		
		if (dot == 256) {
			if (ppumask.show_bkg || ppumask.show_spr) {
				
				if (vram_addr.fine_y_scroll == 7) {
					vram_addr.fine_y_scroll = 0;
					if (vram_addr.coarse_y == 29) {
						vram_addr.coarse_y = 0;
						vram_addr.nametable_y = ~vram_addr.nametable_y;
					}
					else {
						vram_addr.coarse_y++;
					}
				}
				else {
					vram_addr.fine_y_scroll++;
				}
			}
			
		}
		//now for the reason they are called SHIFT registers...
		//shift them after we draw the pixel
		if (ppumask.show_bkg) {
			bkg_patt_shift_lo >>= 1;
			bkg_patt_shift_hi >>= 1;
		}
		

	} else if (dot <= 320) {
		if (dot == 257) {
			if (ppumask.show_bkg || ppumask.show_spr) {
				vram_addr.coarse_x = temp_vram_addr.coarse_x;
				vram_addr.nametable_x = temp_vram_addr.nametable_x;
			}
			
		}
		//fetch data for sprites in next scanline
		fetch_next_scl_sprites();
		
	} else if (dot <= 336) {
		if (dot == 336) {
			evaluate_sprites();
		}
		//fetch data for first 2 tiles in next scanline
		fetch_next_scl_bkground();
		if (ppumask.show_bkg) {
			bkg_patt_shift_lo >>= 1;
			bkg_patt_shift_hi >>= 1;
		}
	} else {
		//do nothing (purpose of cycles 337-340 are unknown and probably not impactful)
	}
}

void post_render()
{

}

void vertical_blank()
{
	if (scanline == 241 && dot == 1) {
		ppustatus.vblank = 1;
		if (ppuctrl.gen_nmi) {
			gen_nmi();
		}
	}
}

void ppu_clock()
{
	if (scanline == -1) {
		//dummy scanline
		pre_render();
	}
	else if (scanline <= 239) {
		//visible scanline
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
	
	dot++;
	if (dot == 341) {
		dot = 0;
		scanline++;
		scanline = (scanline == 261) ? -1 : scanline;
	}
}

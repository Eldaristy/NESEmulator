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
	scanline = 0;

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
	uint8_t mod_coarse_x = vram_addr.coarse_x & 3; //same as "% 2", just wanted to use bit-wise
	uint8_t mod_coarse_y = vram_addr.coarse_y & 3;
	
	
	if (patt_tbl_lo != 0 || patt_tbl_hi != 0) {
		patt_tbl_hi = patt_tbl_hi;
	}

	//that's a nice one... reversing the bits is essential since we use the low bits of the shift registers
	//to draw the pixels each time (and then shift them right). Originally, the pattern bits
	//
	//reverse all the bits of patt_tbl_lo
	patt_tbl_lo = (patt_tbl_lo & 0x7E) | ((patt_tbl_lo & 0x80) >> 7) | ((patt_tbl_lo & 0x01) << 7);
	patt_tbl_lo = (patt_tbl_lo & 0xBD) | ((patt_tbl_lo & 0x40) >> 5) | ((patt_tbl_lo & 0x02) << 5);
	patt_tbl_lo = (patt_tbl_lo & 0xDB) | ((patt_tbl_lo & 0x20) >> 3) | ((patt_tbl_lo & 0x04) << 3);
	patt_tbl_lo = (patt_tbl_lo & 0xE7) | ((patt_tbl_lo & 0x10) >> 1) | ((patt_tbl_lo & 0x08) << 1);

	patt_tbl_hi = (patt_tbl_hi & 0x7E) | ((patt_tbl_hi & 0x80) >> 7) | ((patt_tbl_hi & 0x01) << 7);
	patt_tbl_hi = (patt_tbl_hi & 0xBD) | ((patt_tbl_hi & 0x40) >> 5) | ((patt_tbl_hi & 0x02) << 5);
	patt_tbl_hi = (patt_tbl_hi & 0xDB) | ((patt_tbl_hi & 0x20) >> 3) | ((patt_tbl_hi & 0x04) << 3);
	patt_tbl_hi = (patt_tbl_hi & 0xE7) | ((patt_tbl_hi & 0x10) >> 1) | ((patt_tbl_hi & 0x08) << 1);

	//patt_tbl_lo = ((patt_tbl_lo & 0xF0) >> 4) | ((patt_tbl_lo & 0x0F) << 4);
	//patt_tbl_lo = ((patt_tbl_lo & 0xCC) >> 2) | ((patt_tbl_lo & 0x33) << 2);
	//patt_tbl_lo = ((patt_tbl_lo & 0xAA) >> 1) | ((patt_tbl_lo & 0x55) << 1);

	////reverse all the bits of patt_tbl_hi
	//patt_tbl_hi = ((patt_tbl_hi & 0xF0) >> 4) | ((patt_tbl_hi & 0x0F) << 4);
	//patt_tbl_hi = ((patt_tbl_hi & 0xCC) >> 2) | ((patt_tbl_hi & 0x33) << 2);
	//patt_tbl_hi = ((patt_tbl_hi & 0xAA) >> 1) | ((patt_tbl_lo & 0x55) << 1);

	bkg_patt_shift_lo = bkg_patt_shift_lo & 0xFF | ((uint16_t)(patt_tbl_lo) << 8);
	bkg_patt_shift_hi = bkg_patt_shift_hi & 0xFF | ((uint16_t)(patt_tbl_hi) << 8);

	//bkg_patt_shift_lo = (bkg_patt_shift_lo << 8) | ((patt_tbl_lo) & 0xFF);
	//bkg_patt_shift_hi = (bkg_patt_shift_hi << 8) | ((patt_tbl_hi) & 0xFF);

	if (bkg_patt_shift_lo != 0 || bkg_patt_shift_hi != 0) {
		bkg_attr_shift_lo = bkg_attr_shift_lo;
	}
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
}
void load_spr_shifts()
{

}

void pre_render()
{
	if (dot == 0) {
		ppustatus.vblank = 0;
		if (ppumask.show_bkg || ppumask.show_spr) {
			vram_addr.reg = temp_vram_addr.reg;
		}
		//vram_addr.reg = 0;
		//vram_addr.nametable = 0;
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
		if (patt_tbl_id != 0 && patt_tbl_id != 0x24) {
			patt_tbl_id = patt_tbl_id;
		}
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
		if (patt_tbl_hi || patt_tbl_lo) {
			patt_tbl_hi = patt_tbl_hi;

		}
		break;
	}
	if (!(ppumask.show_bkg || ppumask.show_spr)) {
		return;
	}

	if (dot >= 249 && dot <= 256) { //if we are in the last background tile of the scanline
		return; //don't do anything with the fetch
	}

	if (dot == 328) {
		vram_addr.coarse_x = 0; //reset coarse x so it's first 2 tiles again but in next scanline
	}
	//increment fine_x_scroll, then check if it wraps around and requires
	//incrementing coarse_x... then nametable...
	fine_x_scroll++;
	if (fine_x_scroll == 8) {
		fine_x_scroll = 0;
		if (vram_addr.coarse_x == 31) {
			vram_addr.coarse_x = 0;
			if (vram_addr.fine_y_scroll == 7) {
				vram_addr.fine_y_scroll = 0;
				if (vram_addr.coarse_y == 31) {
					vram_addr.coarse_y = 0;
					if (vram_addr.nametable == 3) {
						vram_addr.nametable = 0;
					} else {
						vram_addr.nametable++;
					}
				} else {
					vram_addr.coarse_y++;
				}
			} else {
				vram_addr.fine_y_scroll++;
			}
		} else {
			vram_addr.coarse_x++;
		}
		
		/*if (vram_addr.coarse_x == 31) {
			vram_addr.coarse_x = 0;
			vram_addr.nametable++;
		}
		if (vram_addr.nametable == 3) {
			vram_addr.nametable = 0;
		}
		break;*/
	}
}
void evaluate_sprites()
{
	assert("not implemented");

	int8_t diff = 0;
	primary_oam_counter = 0;
	secondary_oam_counter = 0;

	for (uint8_t i = 0; i < 8; i++) {
		secondary_oam[i] = (sprite){ 0xFF, 0xFF, 0xFF, 0xFF };
	}

	while (primary_oam_counter / 4 < 64 && secondary_oam_counter / 4 < 8) {
		secondary_oam[secondary_oam_counter / 4] = primary_oam[primary_oam_counter / 4];
		diff = scanline - secondary_oam[secondary_oam_counter * 4].y_top;
		if ((diff >= 0 && diff < 8 && !ppuctrl.spr_size)
			| (diff >= 0 && diff < 16 && ppuctrl.spr_size)) {
			secondary_oam_counter += 4;
		}

		primary_oam_counter += 4;
	}

	//int8_t diff = 0;

	//assert(!"not implemented");
	//if (dot >= 1 && dot <= 64) {
	//	for (uint8_t i = 0; i < 8; i++) {
	//		secondary_oam[i] = (sprite){ 0xFF, 0xFF, 0xFF, 0xFF };
	//	}
	//} else if (dot <= 256) {
	//	switch (dot % 2) {
	//	case 1:
	//		if (secondary_oam_counter / 4 < 8) {
	//			oam_temp = ((uint8_t*)primary_oam)[primary_oam_counter];
	//			break;
	//		} //else - "disable" writing to secondary_oam by simply not reading anything
	//			//so it writes the last value written to secondary_oam.
	//		
	//	
	//	case 0:
	//		//"1"
	//		if (dot == 66) {
	//			primary_oam_counter = 0; //initialize primary_oam_counter
	//		}
	//		if (primary_oam_counter % 4) {
	//			((uint8_t*)secondary_oam)[secondary_oam_counter] = oam_temp;
	//			primary_oam_counter++;
	//			secondary_oam_counter++;

	//			return;
	//		}

	//		((uint8_t*)secondary_oam)[secondary_oam_counter] = oam_temp; 

	//		//+1 because next scanline
	//		diff = scanline + 1 - secondary_oam[secondary_oam_counter * 4].y_top; 
	//		
	//		//check if sprite in range (y axis)
	//		if ((diff >= 0 && diff < 8 && !ppuctrl.spr_size)
	//			| (diff >= 0 && diff < 16 && ppuctrl.spr_size)) {
	//			primary_oam_counter++;
	//			secondary_oam_counter++;

	//			return;
	//		}
	//		
	//		//"2"
	//		if (primary_oam_counter * 4 == 63) //all sprites evaluated
	//		{
	//			primary_oam_counter += 4; 
	//			//4
	//		} else {
	//			primary_oam_counter += 4; //advance to the next sprite in primary_oam
	//			if (secondary_oam_counter / 4 < 8) {
	//				return;
	//			}

	//			//3

	//		}
	//		


	//		if (1) {

	//		} else if (secondary_oam_counter < 8) {
	//			
	//		} else { //secondary_oam_counter == 8

	//		}

	//		oam_temp = secondary_oam[7]; //"ignore" the write
	//		

	//		//"2"
	//		primary_oam_counter++;
	//	}
	//} else if (dot <= 320) {
	//	primary_oam_counter = 0;
	//}
}
void create_pixel()
{
	uint8_t bkg_pixel = 0;
	uint8_t bkg_palette = 0;
	uint8_t spr_pixel = 0; 
	uint8_t spr_palette = 0;
	uint8_t final_pixel = 0;
	uint8_t final_palette = 0;
	uint8_t color[3] = { 0 };

	if (ppumask.show_bkg) {
		bkg_pixel = (bkg_patt_shift_lo & 0x0001) | ((bkg_patt_shift_hi & 0x0001) << 1);
		bkg_palette = (bkg_attr_shift_lo & 0x01) | ((bkg_attr_shift_hi & 0x01) << 1); 
	}
	
	if (bkg_pixel != 0) {
		bkg_pixel = bkg_pixel;
	}
	spr_pixel = 0; //not implemented yet...
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
	if (final_pixel) {
		final_pixel = final_pixel;
	}
	if (final_palette) {
		final_pixel = final_pixel;
	}
	color[0] = colors[palette_ram[final_palette * 4 + final_pixel]][0]; //r
	color[1] = colors[palette_ram[final_palette * 4 + final_pixel]][1]; //g
	color[2] = colors[palette_ram[final_palette * 4 + final_pixel]][2]; //b
	al_draw_pixel(dot - 1, scanline, al_map_rgb(color[0], color[1], color[2]));
	//al_put_pixel(dot - 1, scanline, al_map_rgb(color[0], color[1], color[2]));
	//display_buffer[(dot - 1) * 3][scanline] = colors[((uint8_t*)palette_ram)[final_palette * 4 + final_pixel]];
	if (dot == 256 && scanline == 239) {
		al_flip_display();
	}
	if (dot == 255) {
		vram_addr = vram_addr;
	}
	/*if (dot % 8 == 0) {
		al_flip_display();
	}*/
	//set_pixel(dot - 1, scanline, colors[((uint8_t*)palette_ram)[final_palette * 4 + final_pixel]]);
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
		spr_patt_shift_lo[primary_oam_counter] = ppu_bus_rd(ppuctrl.spr_pattern_table << 12
			| (uint16_t)(secondary_oam[primary_oam_counter].tile_index) << 4
			| scanline - secondary_oam[primary_oam_counter].y_top);
		break;

	case 6:
		spr_patt_shift_lo[primary_oam_counter] = ppu_bus_rd(ppuctrl.spr_pattern_table << 12
			| (uint16_t)(secondary_oam[primary_oam_counter].tile_index) << 4
			| scanline - secondary_oam[primary_oam_counter].y_top + 8);
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

void cycle()
{
	if (scanline == -1) {
		//dummy
		pre_render();
	}
	else if (scanline <= 239) {
		//visible scanline
		//evaluate_sprites();
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

void run_ppu()
{
	ppu_init();
	create_window();
	while (1) {
		cycle();
	}
}
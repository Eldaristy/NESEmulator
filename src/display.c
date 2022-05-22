#include "../include/display.h"

uint8_t display_buffer[256 * 3][240] = { 0 };

void display_init()
{
	al_init();
	display = al_create_display(256 * WINDOW_SCALE, 240 * WINDOW_SCALE);
	int flags = al_get_new_bitmap_flags();
	al_set_new_bitmap_flags(flags | ALLEGRO_MEMORY_BITMAP);
	bitmap = al_create_bitmap(256, 240);
	al_set_new_bitmap_flags(flags);
	al_set_new_bitmap_format(ALLEGRO_PIXEL_FORMAT_RGB_888);
	al_convert_memory_bitmaps();
	
	al_set_target_bitmap(bitmap);
}


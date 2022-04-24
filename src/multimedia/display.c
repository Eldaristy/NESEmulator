#include "display.h"

uint8_t display_buffer[256 * 3][240] = { 0 };

void create_window()
{

	al_init();
	int flags = al_get_new_bitmap_flags();
	al_set_new_bitmap_flags(flags | ALLEGRO_MEMORY_BITMAP);
	bitmap = al_create_bitmap(256, 240);
	al_set_new_bitmap_flags(flags);
	al_set_new_bitmap_format(ALLEGRO_PIXEL_FORMAT_RGB_888);
	//ALLEGRO_FILE* memfile = al_open_memfile(display_buffer, 256 * 240 * 3, "r");
	//char* ident = al_identify_bitmap(memfile);
	//bitmap = al_load_bitmap_f(memfile, ident);

	ALLEGRO_DISPLAY* display = al_create_display(256 * WINDOW_SCALE, 240 * WINDOW_SCALE);

}
void set_pixel(uint8_t x, uint8_t y, uint8_t rgb[3])
{
	al_draw_pixel(x, y, al_map_rgb(rgb[0], rgb[1], rgb[2]));
	al_flip_display();
}

void update_display()
{
	al_draw_bitmap(bitmap, 256, 240, NULL);
}

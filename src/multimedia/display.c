#include "display.h"

void create_window(const int* pixels)
{

	al_init();
	ALLEGRO_DISPLAY* display = al_create_display(256 * WINDOW_SCALE, 240 * WINDOW_SCALE);

}
void set_pixel(uint8_t x, uint8_t y, uint8_t rgb[3])
{
	al_draw_pixel(x, y, al_map_rgb(rgb[0], rgb[1], rgb[2]));
	al_flip_display();
}



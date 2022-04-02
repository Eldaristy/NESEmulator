#include "display.h"

void create_window(const int* pixels)
{

	al_init();
	ALLEGRO_DISPLAY* display = al_create_display(256 * WINDOW_SCALE, 240 * WINDOW_SCALE);
	al_draw_pixel(128, 120, al_map_rgb(255, 0, 255));
	al_flip_display();
	return 0;
}	



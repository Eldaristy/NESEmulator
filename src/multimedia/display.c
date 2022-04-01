#include "display.h"

void create_window(const int* pixels)
{
	/*sfVideoMode mode = { 256 * WINDOW_SCALE, 240 * WINDOW_SCALE, 24 };
	sfWindow* window = sfWindow_create(mode, "NEScafe", sfDefaultStyle, NULL);

	sfImage_createFromPixels(20 * WINDOW_SCALE, 18 * WINDOW_SCALE, pixels);
	sfColor green = sfColor_fromRGB(0, 255, 0);
	sfImage_setPixel(window, 20, 20, green);
	while (sfWindow_isOpen(window)) {
		sfEvent event;
		while (sfWindow_pollEvent(window, &event)) {
			if (event.type == sfEvtClosed) {
				sfWindow_close(window);
			}
		}
		
	}*/
	al_init();
	ALLEGRO_DISPLAY* display = al_create_display(256 * WINDOW_SCALE, 240 * WINDOW_SCALE);
	al_draw_pixel(128, 120, al_map_rgb(255, 0, 255));
	al_flip_display();
	return 0;
}	



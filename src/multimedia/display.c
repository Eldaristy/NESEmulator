#include "display.h"
#include <SFML/Window.h>

int display()
{
	sfVideoMode mode = { 256 * WINDOW_SCALE, 240 * WINDOW_SCALE, 24 };
	sfWindow_create(mode, "NEScafe", sfDefaultStyle, NULL);

	return 0;
}	
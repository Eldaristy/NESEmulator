#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <allegro5/allegro.h>

#define WINDOW_SCALE 3

ALLEGRO_BITMAP* bitmap;
ALLEGRO_DISPLAY* display;

void display_init();

#endif
#ifndef DISPLAY_H
#define DISPLAY_H

#include <allegro5/allegro.h>
#include <stdint.h>

#define WINDOW_SCALE 1

ALLEGRO_BITMAP* bitmap;

void create_window();
void set_pixel(uint8_t, uint8_t, uint8_t[3]);
void draw_noise(const int*);
#endif
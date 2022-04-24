#ifndef DISPLAY_H
#define DISPLAY_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_memfile.h>
#include <stdint.h>

#define WINDOW_SCALE 1
uint8_t display_buffer[256 * 3][240];

ALLEGRO_BITMAP* bitmap;

void create_window();
void set_pixel(uint8_t, uint8_t, uint8_t[3]);
void draw_noise(const int*);
void update_display();
#endif
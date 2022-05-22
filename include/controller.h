#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdint.h>
#include <allegro5/allegro5.h>

void controller_init();
void run_controller();

ALLEGRO_KEYBOARD_STATE key_state;

union {
	struct {
		uint8_t a : 1;
		uint8_t b : 1;
		uint8_t select : 1;
		uint8_t start : 1;
		uint8_t up : 1;
		uint8_t down : 1;
		uint8_t left : 1;
		uint8_t right : 1;
	};
	uint8_t all_buttons;
} buttons;

//it's called a "strobe" (for some reason). What it means is that it's a signal which is
//delivered by the cpu, and is either 0 or 1.
//when the strobe is high (set to 1), the controller loads the shift register with the data of 
//the pressed buttons, each bit by the order that the buttons were defined above.
//then, when the strobe is set to 0, after each time the shift register is read 
//and returns the value of the first bit, the shift register is shifted (to the right)
//so the next time it will be read it will return the next bit.
//it means, the first read will return the A button state, next read B, then Select...
uint8_t strobe; 
uint8_t controller_shift_reg;
#endif
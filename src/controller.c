#include "../include/controller.h"

void controller_init()
{
	buttons.all_buttons = 0;
	strobe = 0;
	controller_shift_reg = 0;

	al_install_keyboard();
}

void run_controller()
{
		al_get_keyboard_state(&key_state);
		buttons.a = al_key_down(&key_state, ALLEGRO_KEY_J);
		buttons.b = al_key_down(&key_state, ALLEGRO_KEY_K);
		buttons.select = al_key_down(&key_state, ALLEGRO_KEY_RSHIFT);
		buttons.start = al_key_down(&key_state, ALLEGRO_KEY_ENTER)
			|| al_key_down(&key_state, ALLEGRO_KEY_BACKSPACE);
		buttons.up = al_key_down(&key_state, ALLEGRO_KEY_W);
		buttons.down = al_key_down(&key_state, ALLEGRO_KEY_S);
		buttons.left = al_key_down(&key_state, ALLEGRO_KEY_A);
		buttons.right = al_key_down(&key_state, ALLEGRO_KEY_D);	
}
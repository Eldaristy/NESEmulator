#include <Windows.h>
#include <stdio.h>
#include "multimedia/display.h"
#include "../include/cpu.h"
#include "../include/ppu.h"
#include "../include/cartidge.h"

int main(int argc, char** argv)
{
	argc = 2; 

	if (argc == 1) {
		printf(".nes file not specified\n");
		return 1;
	}

	parse_file("C:\\Users\\user\\Desktop\\donkey_kong.nes");
	create_window();

	cpu_init();
	reset();

	ppu_init();

	while (TRUE) {
		run_clock();

		cycle();
		cycle();
		cycle();

		/*printf("%x, A:%x X:%x Y:%x P:%x SP:%x PC:%x\n",
			fetched_opcode, context.a, context.x, context.y, context.flags, context.sp, context.pc);*/

	}

	/*HANDLE ppu_thread = CreateThread(NULL, NULL, &run_ppu, NULL, NULL, NULL);
	HANDLE cpu_thread = CreateThread(NULL, NULL, &run_clock, NULL, NULL, NULL);
	
	WaitForSingleObject(ppu_thread, INFINITE);*/

/*
	create_window(cpu_ram);
	run_clock();
	int dummy = 0;
	scanf_s("\n");
	*/return 0;
}

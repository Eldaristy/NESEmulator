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


	run_clock();
	
/*
	create_window(cpu_ram);
	run_clock();
	int dummy = 0;
	scanf_s("\n");
	*/return 0;
}

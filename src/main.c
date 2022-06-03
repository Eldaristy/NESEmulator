#include <stdio.h>
#include "../include/display.h"
#include "../include/cpu.h"
#include "../include/ppu.h"
#include "../include/cartidge.h"
#include <Windows.h>
int main(int argc, char** argv)
{
	argc = 2; 

	if (argc == 1) {
		printf(".nes file not specified\n");
		return 1;
	}

	parse_file("C:\\Users\\user\\Desktop\\nestests\\kung_fu.nes");
	//parse_file(argv[1]);
	cpu_init();
	reset();

	ppu_init();
	display_init();
	controller_init();

	//HANDLE thread = CreateThread(NULL, NULL, run_controller, NULL, NULL, NULL);
	

	while (1) {
		cpu_clock();

		ppu_clock();
		ppu_clock();
		ppu_clock();
		
		//run_controller();
		/*printf("%x, A:%x X:%x Y:%x P:%x SP:%x PC:%x\n",
			fetched_opcode, context.a, context.x, context.y, context.flags, context.sp, context.pc);
		*/
			

	}
	
	return 0;
}

void test()
{
	while (1) {
		cpu_clock();

		ppu_clock();
		ppu_clock();
		ppu_clock();

		//run_controller();
		/*printf("%x, A:%x X:%x Y:%x P:%x SP:%x PC:%x\n",
			fetched_opcode, context.a, context.x, context.y, context.flags, context.sp, context.pc);
		*/


	}
}
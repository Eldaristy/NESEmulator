#include "multimedia/display.h"
#include <stdio.h>
#include "../include/ram.h"
#include "../include/cpu.h"
int main()
{
	create_window(cpu_ram);
	run_clock();
	int dummy = 0;
	scanf_s("\n");
	return 0;
}

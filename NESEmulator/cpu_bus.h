#ifndef CPU_BUS_H
#define CPU_BUS_H

#include <stdint.h>

uint16_t cpu_bus_rd(uint16_t);
void cpu_bus_wr(uint16_t, uint16_t);

#endif 
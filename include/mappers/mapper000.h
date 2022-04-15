#ifndef MAPPER000_H
#define MAPPER000_H

#include <stdint.h>
#include "../cartidge.h"

uint8_t cpu_m000_rd(uint16_t);
void cpu_m000_wr(uint16_t, uint8_t);
uint8_t ppu_m000_rd(uint16_t);
void ppu_m000_wr(uint16_t, uint8_t);

#endif
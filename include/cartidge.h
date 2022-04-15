#ifndef CARTIDGE_H
#define CARTIDGE_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "mappers/mapper000.h"
#include "ppu_bus.h"

#define KB 1024


typedef struct {
	uint8_t(*cpu_rd)(uint16_t);
	void (*cpu_wr)(uint16_t, uint8_t);
	uint8_t(*ppu_rd)(uint16_t);
	void (*ppu_wr)(uint16_t, uint8_t);
} mapper;

mapper mappers[]; //all mappers that exist

//this variable corresponds to the mapper functions used in the game running.
//it is set dynamically, while the cartidge figures out which mapper the game uses
mapper used_mapper; 

static void parse_header(const FILE*);
void parse_file(const char*);

//all sections of the .ines file.
//sections with determined size can be STATICALLY allocated,
//whereas sections with undetermined size are DYNAMICALLY allocated.
uint8_t header[16];
uint8_t* trainer; // 0 or 512 bytes
uint8_t* prg_rom_data; // 16KB * x 
uint8_t* chr_rom_data; // 8KB * x 
uint8_t* inst_rom_data; // 0 or 8KB
uint8_t* p_rom_data; // 0 or 32 bytes

//The 16 bytes long header is constructed by the following structure:
uint8_t nes_text[4]; //0-3 - "NES" followed by MS-DOS end-of-file
uint8_t prg_banks; //4
uint8_t chr_banks; //5
union FLAGS_6 {
	struct {
		uint8_t mirroring : 1;
		uint8_t prg_ram : 1;
		uint8_t trainer : 1;
		uint8_t ignore_mirroring : 1;
		uint8_t lower_mapper_n : 4;
	};
	uint8_t byte;
} flags_6;

union FLAGS_7 {
	struct {
		uint8_t vs_unisystem : 1;
		uint8_t playchoice : 1;
		uint8_t nes_2_0 : 2; //if it equals to 2
		uint8_t higher_mapper_n : 4;
	};
	uint8_t byte;
} flags_7;

//more flags that won't be used for now...
#endif
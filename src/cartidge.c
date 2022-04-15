#include "../include/cartidge.h"

mapper mappers[0x100] = { 
	{cpu_m000_rd, cpu_m000_wr, ppu_m000_rd, ppu_m000_wr}
};

static void parse_header(const FILE* cartidge)
{
	uint8_t nes_signature[4] = { 'N', 'E', 'S', 0x1A };

	fread(header, sizeof(uint8_t), 16, cartidge);

	//store NES signature
	memcpy(nes_text, header, 4);
	assert(!memcmp(nes_text, nes_signature, 4));

	//store PRG ROM size
	prg_banks = header[4];

	//store CHR ROM size
	chr_banks = header[5];

	//store flags
	flags_6.byte = header[6];
	flags_7.byte = header[7];
}

void parse_file(const char* path)
{
	FILE* cartidge = NULL;
	size_t total_prg_size = 0;
	size_t total_chr_size = 0;
	uint8_t n_mapper = 0;

	cartidge = fopen(path, "rb");
	assert(cartidge);

	parse_header(cartidge);

	//parse, allocate and load trainer ONLY IF PRESENT
	if (flags_6.trainer) {
		trainer = (uint8_t*)malloc(512); 
		assert(trainer);
		fread(trainer, sizeof(uint8_t), 512, cartidge);
	}

	//parse, allocate and load prg_rom
	total_prg_size = 16 * KB * (size_t)prg_banks;
	prg_rom_data = (uint8_t*)malloc(total_prg_size);
	assert(prg_rom_data);
	fread(prg_rom_data, sizeof(uint8_t), total_prg_size, cartidge);

	//parse, allocate and load chr_rom
	total_chr_size = 8 * KB * (size_t)chr_banks;
	chr_rom_data = (uint8_t*)malloc(total_chr_size);
	assert(chr_rom_data);
	fread(chr_rom_data, sizeof(uint8_t), total_chr_size, cartidge);

	//set used_mapper to be the required mapper
	n_mapper = flags_6.lower_mapper_n | (flags_7.higher_mapper_n << 4);
	used_mapper = mappers[n_mapper];

	//finally we are done with the .nes file
	fclose(cartidge);
}
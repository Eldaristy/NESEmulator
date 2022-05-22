#include "../include/cpu.h"

opcode opcode_table[0x100] = {
	{i_BRK,a_IMP, 7}, {i_ORA,a_XND, 6}, {i_JAM,a_IMP, 2}, {i_SLO,a_XND, 8}, {i_NOP,a_ZPG, 3}, {i_ORA,a_ZPG, 3}, {i_ASL,a_ZPG, 5}, {i_SLO,a_ZPG, 5}, {i_PHP,a_IMP, 3}, {i_ORA,a_IMM, 2}, {i_ASL,a_ACC, 2}, {i_ANC,a_IMM, 2}, {i_NOP,a_ABS, 4}, {i_ORA,a_ABS, 4}, {i_ASL,a_ABS, 6}, {i_SLO,a_ABS, 6},
	{i_BPL,a_REL, 2}, {i_ORA,a_INY, 5}, {i_JAM,a_IMP, 2}, {i_SLO,a_INY, 8}, {i_NOP,a_ZPX, 4}, {i_ORA,a_ZPX, 4}, {i_ASL,a_ZPX, 6}, {i_SLO,a_ZPX, 6}, {i_CLC,a_IMP, 2}, {i_ORA,a_ABY, 4}, {i_NOP,a_IMP, 2}, {i_SLO,a_ABY, 7}, {i_NOP,a_ABX, 4}, {i_ORA,a_ABX, 4}, {i_ASL,a_ABX, 7}, {i_SLO,a_ABX, 7},
	{i_JSR,a_ABS, 6}, {i_AND,a_XND, 6}, {i_JAM,a_IMP, 2}, {i_RLA,a_XND, 8}, {i_BIT,a_ZPG, 3}, {i_AND,a_ZPG, 3}, {i_ROL,a_ZPG, 5}, {i_RLA,a_ZPG, 5}, {i_PLP,a_IMP, 4}, {i_AND,a_IMM, 2}, {i_ROL,a_ACC, 2}, {i_ANC,a_IMM, 2}, {i_BIT,a_ABS, 4}, {i_AND,a_ABS, 4}, {i_ROL,a_ABS, 6}, {i_RLA,a_ABS, 6},
	{i_BMI,a_REL, 2}, {i_AND,a_INY, 5}, {i_JAM,a_IMP, 2}, {i_RLA,a_INY, 8}, {i_NOP,a_ZPX, 4}, {i_AND,a_ZPX, 4}, {i_ROL,a_ZPX, 6}, {i_RLA,a_ZPX, 6}, {i_SEC,a_IMP, 2}, {i_AND,a_ABY, 4}, {i_NOP,a_IMP, 2}, {i_RLA,a_ABY, 7}, {i_NOP,a_ABX, 4}, {i_AND,a_ABX, 4}, {i_ROL,a_ABX, 7}, {i_RLA,a_ABX, 7},
	{i_RTI,a_IMP, 6}, {i_EOR,a_XND, 6}, {i_JAM,a_IMP, 2}, {i_SRE,a_XND, 8}, {i_NOP,a_ZPG, 3}, {i_EOR,a_ZPG, 3}, {i_LSR,a_ZPG, 5}, {i_SRE,a_ZPG, 5}, {i_PHA,a_IMP, 3}, {i_EOR,a_IMM, 2}, {i_LSR,a_ACC, 2}, {i_ALR,a_IMM, 2}, {i_JMP,a_ABS, 3}, {i_EOR,a_ABS, 4}, {i_LSR,a_ABS, 6}, {i_SRE,a_ABS, 6},
	{i_BVC,a_REL, 2}, {i_EOR,a_INY, 5}, {i_JAM,a_IMP, 2}, {i_SRE,a_INY, 8}, {i_NOP,a_ZPX, 4}, {i_EOR,a_ZPX, 4}, {i_LSR,a_ZPX, 6}, {i_SRE,a_ZPX, 6}, {i_CLI,a_IMP, 2}, {i_EOR,a_ABY, 4}, {i_NOP,a_IMP, 2}, {i_SRE,a_ABY, 7}, {i_NOP,a_ABX, 4}, {i_EOR,a_ABX, 4}, {i_LSR,a_ABX, 7}, {i_SRE,a_ABX, 7},
	{i_RTS,a_IMP, 6}, {i_ADC,a_XND, 6}, {i_JAM,a_IMP, 2}, {i_RRA,a_XND, 8}, {i_NOP,a_ZPG, 3}, {i_ADC,a_ZPG, 3}, {i_ROR,a_ZPG, 5}, {i_RRA,a_ZPG, 5}, {i_PLA,a_IMP, 4}, {i_ADC,a_IMM, 2}, {i_ROR,a_ACC, 2}, {i_ARR,a_IMM, 2}, {i_JMP,a_IND, 5}, {i_ADC,a_ABS, 4}, {i_ROR,a_ABS, 6}, {i_RRA,a_ABS, 6},
	{i_BVS,a_REL, 2}, {i_ADC,a_INY, 5}, {i_JAM,a_IMP, 2}, {i_RRA,a_INY, 8}, {i_NOP,a_ZPX, 4}, {i_ADC,a_ZPX, 4}, {i_ROR,a_ZPX, 6}, {i_RRA,a_ZPX, 6}, {i_SEI,a_IMP, 2}, {i_ADC,a_ABY, 4}, {i_NOP,a_IMP, 2}, {i_RRA,a_ABY, 7}, {i_NOP,a_ABX, 4}, {i_ADC,a_ABX, 4}, {i_ROR,a_ABX, 7}, {i_RRA,a_ABX, 7},
	{i_NOP,a_IMM, 2}, {i_STA,a_XND, 6}, {i_NOP,a_IMM, 2}, {i_SAX,a_XND, 6}, {i_STY,a_ZPG, 3}, {i_STA,a_ZPG, 3}, {i_STX,a_ZPG, 3}, {i_SAX,a_ZPG, 3}, {i_DEY,a_IMP, 2}, {i_NOP,a_IMM, 2}, {i_TXA,a_IMP, 2}, {i_ANE,a_IMM, 2}, {i_STY,a_ABS, 4}, {i_STA,a_ABS, 4}, {i_STX,a_ABS, 4}, {i_SAX,a_ABS, 4},
	{i_BCC,a_REL, 2}, {i_STA,a_INY, 6}, {i_JAM,a_IMP, 2}, {i_SHA,a_INY, 6}, {i_STY,a_ZPX, 4}, {i_STA,a_ZPX, 4}, {i_STX,a_ZPY, 4}, {i_SAX,a_ZPY, 4}, {i_TYA,a_IMP, 2}, {i_STA,a_ABY, 5}, {i_TXS,a_IMP, 2}, {i_TAS,a_ABY, 5}, {i_SHY,a_ABX, 4}, {i_STA,a_ABX, 5}, {i_SHX,a_ABY, 5}, {i_SHA,a_ABY, 5},
	{i_LDY,a_IMM, 2}, {i_LDA,a_XND, 6}, {i_LDX,a_IMM, 2}, {i_LAX,a_XND, 6}, {i_LDY,a_ZPG, 3}, {i_LDA,a_ZPG, 3}, {i_LDX,a_ZPG, 3}, {i_LAX,a_ZPG, 3}, {i_TAY,a_IMP, 2}, {i_LDA,a_IMM, 2}, {i_TAX,a_IMP, 2}, {i_LAX,a_IMM, 2}, {i_LDY,a_ABS, 4}, {i_LDA,a_ABS, 4}, {i_LDX,a_ABS, 4}, {i_LAX,a_ABS, 4},
	{i_BCS,a_REL, 2}, {i_LDA,a_INY, 5}, {i_JAM,a_IMP, 2}, {i_LAX,a_INY, 5}, {i_LDY,a_ZPX, 4}, {i_LDA,a_ZPX, 4}, {i_LDX,a_ZPY, 4}, {i_LAX,a_ZPY, 4}, {i_CLV,a_IMP, 2}, {i_LDA,a_ABY, 4}, {i_TSX,a_IMP, 2}, {i_LAS,a_ABY, 4}, {i_LDY,a_ABX, 4}, {i_LDA,a_ABX, 4}, {i_LDX,a_ABY, 4}, {i_LAX,a_ABY, 4},
	{i_CPY,a_IMM, 2}, {i_CMP,a_XND, 6}, {i_NOP,a_IMM, 2}, {i_DCP,a_XND, 8}, {i_CPY,a_ZPG, 3}, {i_CMP,a_ZPG, 3}, {i_DEC,a_ZPG, 5}, {i_DCP,a_ZPG, 5}, {i_INY,a_IMP, 2}, {i_CMP,a_IMM, 2}, {i_DEX,a_IMP, 2}, {i_SBX,a_IMM, 2}, {i_CPY,a_ABS, 4}, {i_CMP,a_ABS, 4}, {i_DEC,a_ABS, 6}, {i_DCP,a_ABS, 6},
	{i_BNE,a_REL, 2}, {i_CMP,a_INY, 5}, {i_JAM,a_IMP, 2}, {i_DCP,a_INY, 8}, {i_NOP,a_ZPX, 4}, {i_CMP,a_ZPX, 4}, {i_DEC,a_ZPX, 6}, {i_DCP,a_ZPX, 6}, {i_CLD,a_IMP, 2}, {i_CMP,a_ABY, 4}, {i_NOP,a_IMP, 2}, {i_DCP,a_ABY, 7}, {i_NOP,a_ABX, 4}, {i_CMP,a_ABX, 4}, {i_DEC,a_ABX, 7}, {i_DCP,a_ABX, 7},
	{i_CPX,a_IMM, 2}, {i_SBC,a_XND, 6}, {i_NOP,a_IMM, 2}, {i_ISC,a_XND, 8}, {i_CPX,a_ZPG, 3}, {i_SBC,a_ZPG, 3}, {i_INC,a_ZPG, 5}, {i_ISC,a_ZPG, 5}, {i_INX,a_IMP, 2}, {i_SBC,a_IMM, 2}, {i_NOP,a_IMP, 2}, {i_SBC,a_IMM, 2}, {i_CPX,a_ABS, 4}, {i_SBC,a_ABS, 4}, {i_INC,a_ABS, 6}, {i_ISC,a_ABS, 6},
	{i_BEQ,a_REL, 2}, {i_SBC,a_INY, 5}, {i_JAM,a_IMP, 2}, {i_ISC,a_INY, 8}, {i_NOP,a_ZPX, 4}, {i_SBC,a_ZPX, 4}, {i_INC,a_ZPX, 6}, {i_ISC,a_ZPX, 6}, {i_SED,a_IMP, 2}, {i_SBC,a_ABY, 4}, {i_NOP,a_IMP, 2}, {i_ISC,a_ABY, 7}, {i_NOP,a_ABX, 4}, {i_SBC,a_ABX, 4}, {i_INC,a_ABX, 7}, {i_ISC,a_ABX, 7}
};

void cpu_init()
{
	nmi_line = 0;

	context.a = 0;
	context.flags = 0;
	context.flags = SET_FLAG_ON(FLAG_UNUSED);
	context.pc = 0;
	context.sp = 0;
	context.x = 0;
	context.y = 0;

	effective_addr = 0;
	fetched_opcode = 0;
	fetched_data = 0;
}

void reset()
{
	//technically it's set to 0x00 and then the return address and status
	//registers are pushed, but these are read cycles so it's ignored.
	//there are 3 pushes to the stack and that's why I set it to 0xFD.
	context.sp = 0xFD; 

	context.pc = (uint16_t)cpu_bus_rd(0xFFFC);
	context.pc |= ((uint16_t)cpu_bus_rd(0xFFFD) << 8); //RESET vector

	context.flags = SET_FLAG_ON(FLAG_I);

	cpu_cycles = 8;
}

//does what the BRK instruction does, except for a few differences	
void nmi()
{
	//1st difference: the I flag doesn't affect its execution (the NMI doesn't care about it)
	//2nd difference: doesn't increment context.pc
	STK_PUSH(context.pc >> 8); //high byte
	STK_PUSH(context.pc & 0xFF); //low byte
	STK_PUSH(context.flags | FLAG_UNUSED); //3rd difference: doesn't push the B flag set

	context.pc = (uint16_t)cpu_bus_rd(0xFFFA);
	context.pc|= ((uint16_t)cpu_bus_rd(0xFFFB) << 8); //4th difference - NMI vector

	context.flags = SET_FLAG_ON(FLAG_I);
	
	cpu_cycles = 8;
}

//similar to NMI interrupt and BRK instructions, but with 2 differences to the BRK
void irq()
{
	if (!(context.flags & FLAG_I)) { //I flag disables any interrupt except for NMI
		//1st difference: doesn't increment context.pc

		STK_PUSH(context.pc >> 8); //high byte
		STK_PUSH(context.pc & 0xFF); //low byte
		STK_PUSH(context.flags | FLAG_UNUSED); //2nd diffrence - doesn't push the B flag set

		context.pc = (uint16_t)cpu_bus_rd(0xFFFE);
		context.pc |= ((uint16_t)cpu_bus_rd(0xFFFF) << 8); //IRQ/BRK vector

		context.flags = SET_FLAG_ON(FLAG_I);

		cpu_cycles = 7;
	}
}

void cpu_clock()
{
	if (cpu_cycles == 0) {
		fetched_opcode = cpu_bus_rd(context.pc);
		cpu_cycles = opcode_table[fetched_opcode].cycles;
		opcode_table[fetched_opcode].addressing_mode();
		opcode_table[fetched_opcode].instruction();
		//check for hardware interrupts
		if (nmi_line) {
 			nmi();
			nmi_line = 0;
		} else if (irq_line) {
			irq();
			irq_line = 0;
		}
	}
	cpu_cycles--;
}
void a_ACC()
{
	fetched_data = context.a;
	context.pc++;
}
void a_ABS()
{
	effective_addr = cpu_bus_rd(context.pc + 1); //low byte read from lower address
	effective_addr += cpu_bus_rd(context.pc + 2) << 8; //high byte read from higher address
	//fetched_data = cpu_bus_rd(effective_addr);
	context.pc += 3;
}
void a_ABX()
{
	effective_addr = cpu_bus_rd(context.pc + 1); //low byte read from lower address
	effective_addr += cpu_bus_rd(context.pc + 2) << 8; //high byte read from higher address
	if (effective_addr >> 8 != (effective_addr + context.x) >> 8) {
		cpu_cycles++;
	}
	effective_addr += context.x;
	//fetched_data = cpu_bus_rd(effective_addr);
	context.pc += 3;
}
void a_ABY()
{
	effective_addr = cpu_bus_rd(context.pc + 1); //low byte read from lower address
	effective_addr += cpu_bus_rd(context.pc + 2) << 8; //high byte read from higher address
	if (effective_addr >> 8 != (effective_addr + context.y) >> 8) {
		cpu_cycles++;
	}
	effective_addr += context.y;
	//fetched_data = cpu_bus_rd(effective_addr);
	context.pc += 3;
}
void a_IMM()
{
	effective_addr = context.pc + 1;
	//fetched_data = cpu_bus_rd(effective_addr);
	context.pc += 2;
}
void a_IMP()
{
	context.pc++;
}
void a_IND() 
{
	effective_addr = cpu_bus_rd(context.pc + 1);
	effective_addr += cpu_bus_rd(context.pc + 2) << 8;
	if ((uint8_t)effective_addr == 0xFF) {
		effective_addr = cpu_bus_rd(effective_addr) + (cpu_bus_rd(effective_addr - 0xFF) << 8); //emulate the 0xFF wrapping around bug
	} else {
		effective_addr = cpu_bus_rd(effective_addr) + (cpu_bus_rd(effective_addr + 1) << 8);
	}
		 
	//fetched_data = 0;
	context.pc += 3;
}
void a_INY() 
{
	effective_addr = cpu_bus_rd(context.pc + 1);
	//effective_addr += cpu_bus_rd(context.pc + 2) << 8;
	if ((uint8_t)effective_addr == 0xFF) {
		effective_addr = cpu_bus_rd(effective_addr) + (cpu_bus_rd(effective_addr - 0xFF) << 8); //emulate the 0xFF wrapping around bug
	}
	else {
		effective_addr = cpu_bus_rd(effective_addr) + (cpu_bus_rd(effective_addr + 1) << 8);
	}

	if (effective_addr >> 8 != (effective_addr + context.y) >> 8) {
		cpu_cycles++;
	}
	effective_addr += context.y;
	//fetched_data = cpu_bus_rd(effective_addr);
	context.pc += 2;
}
void a_XND()
{
	effective_addr = (cpu_bus_rd(context.pc + 1) + context.x) & 0xFF; //without carry
	if ((uint8_t)effective_addr == 0xFF) {
		effective_addr = cpu_bus_rd(effective_addr) + (cpu_bus_rd(effective_addr - 0xFF) << 8); //emulate the 0xFF wrapping around bug
	} else {
		effective_addr = cpu_bus_rd(effective_addr) + (cpu_bus_rd(effective_addr + 1) << 8);
	}
	//effective_addr = cpu_bus_rd(effective_addr); //some instructions use the fetched data as an address
	//fetched_data = effective_addr; //while others use it as data
	context.pc += 2;
}
void a_REL()
{ 
	effective_addr = context.pc;
	//fetched_data = (int8_t)cpu_bus_rd(context.pc + 1);
	context.pc += 2;
}
void a_ZPG() 
{
	effective_addr = cpu_bus_rd(context.pc + 1);
	//fetched_data = cpu_bus_rd(effective_addr);
	context.pc += 2;
}
void a_ZPX() 
{
	//uint8_t effective_addr = 0; //since it's zero-paged, it's only 8 bits
	effective_addr = cpu_bus_rd(context.pc + 1);
	effective_addr += context.x;
	effective_addr &= 0xFF;
	//fetched_data = cpu_bus_rd(effective_addr);
	context.pc += 2;
}
void a_ZPY()
{
	//uint8_t effective_addr = 0; //since it's zero-paged, it's only 8 bits
	effective_addr = cpu_bus_rd(context.pc + 1);
	effective_addr += context.y;
	effective_addr &= 0xFF;
	//fetched_data = cpu_bus_rd(effective_addr);
	context.pc += 2;
}

//instructions
void i_ADC()
{
	fetched_data = cpu_bus_rd(effective_addr);
	result = fetched_data + context.a + (context.flags & FLAG_C);

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
	SET_C_FLAG(result);
	SET_V_FLAG(result);

	context.a = result;
}
void i_AND()
{
	fetched_data = cpu_bus_rd(effective_addr);
	result = fetched_data & context.a;
	context.a = (uint8_t)result;

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
}
void i_ASL()
{
	if(opcode_table[fetched_opcode].addressing_mode == a_ACC) {
		result = context.a << 1;
		context.a = (uint8_t)result;
	}
	else {
		fetched_data = cpu_bus_rd(effective_addr);
		result = fetched_data << 1;
		cpu_bus_wr(effective_addr, (uint8_t)result);
	}

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
	SET_C_FLAG(result);
}
void i_BCC()
{
	if (!(context.flags & FLAG_C)) {
		fetched_data = (int8_t)cpu_bus_rd(context.pc - 1);
		if (context.pc >> 8 != (context.pc + (int8_t)fetched_data) >> 8) {
			cpu_cycles++;
		}
		context.pc += (int8_t)fetched_data;
		cpu_cycles++;
	}
}
void i_BCS() {
	if (context.flags & FLAG_C) {
		fetched_data = (int8_t)cpu_bus_rd(context.pc - 1);
		if (context.pc >> 8 != (context.pc + (int8_t)fetched_data) >> 8) {
			cpu_cycles++;
		}
		context.pc += (int8_t)fetched_data;
		cpu_cycles++;
	}
} 
void i_BEQ() {
	if (context.flags & FLAG_Z) {
		fetched_data = (int8_t)cpu_bus_rd(context.pc - 1);
		if (context.pc >> 8 != (context.pc + (int8_t)fetched_data) >> 8) {
			cpu_cycles++;
		}
		context.pc += (int8_t)fetched_data;
		cpu_cycles++;
	}
}
void i_BIT() {
	fetched_data = cpu_bus_rd(effective_addr);
	result = fetched_data & context.a;

	context.flags = fetched_data & 0x80 ? SET_FLAG_ON(FLAG_N) : SET_FLAG_OFF(FLAG_N);
	SET_Z_FLAG((uint8_t)result);
	context.flags = fetched_data & 0x40 ? SET_FLAG_ON(FLAG_V) : SET_FLAG_OFF(FLAG_V);
}
void i_BMI() {
	if (context.flags & FLAG_N) {
		fetched_data = (int8_t)cpu_bus_rd(context.pc - 1);
		if (context.pc >> 8 != (context.pc + (int8_t)fetched_data) >> 8) {
			cpu_cycles++;
		}
		context.pc += (int8_t)fetched_data;
		cpu_cycles++;
	}
}
void i_BNE() {
	if (!(context.flags & FLAG_Z)) {
		fetched_data = (int8_t)cpu_bus_rd(context.pc - 1);
		if (context.pc >> 8 != (context.pc + (int8_t)fetched_data) >> 8) {
			cpu_cycles++;
		}
		context.pc += (int8_t)fetched_data;
		cpu_cycles++;
	}
}
void i_BPL() {
	if (!(context.flags & FLAG_N)) {
		fetched_data = (int8_t)cpu_bus_rd(context.pc - 1);
		if (context.pc >> 8 != (context.pc + (int8_t)fetched_data) >> 8) {
			cpu_cycles++;
		}
		context.pc += (int8_t)fetched_data;
		cpu_cycles++;
	}
}
void i_BRK() {
	if (!(context.flags & FLAG_I)) { //I flag disables any interrupt except for NMI
		context.pc++; //ALWAYS THERE'S A PADDING BYTE AFTER THE OPCODE

		STK_PUSH(context.pc >> 8); //high byte
		STK_PUSH(context.pc & 0xFF); //low byte
		STK_PUSH(context.flags | FLAG_UNUSED | FLAG_B);
		
		context.pc = (uint16_t)cpu_bus_rd(0xFFFE) 
			| ((uint16_t)cpu_bus_rd(0xFFFF) << 8); //IRQ/BRK vector

		context.flags = SET_FLAG_ON(FLAG_I);
	}
}
void i_BVC() {
	if (!(context.flags & FLAG_V)) {
		fetched_data = (int8_t)cpu_bus_rd(context.pc - 1);
		if (context.pc >> 8 != (context.pc + (int8_t)fetched_data) >> 8) {
			cpu_cycles++;
		}
		context.pc += (int8_t)fetched_data;
		cpu_cycles++;
	}
}
void i_BVS() {
	if (context.flags & FLAG_V) {
		fetched_data = (int8_t)cpu_bus_rd(context.pc - 1);
		if (context.pc >> 8 != (context.pc + (int8_t)fetched_data) >> 8) {
			cpu_cycles++;
		}
		context.pc += (int8_t)fetched_data;
		cpu_cycles++;
	}
}
void i_CLC() {
	context.flags = SET_FLAG_OFF(FLAG_C);
}
void i_CLD() {
	context.flags = SET_FLAG_OFF(FLAG_D);
}
void i_CLI() {
	context.flags = SET_FLAG_OFF(FLAG_I);
}
void i_CLV() {
	context.flags = SET_FLAG_OFF(FLAG_V);
}
void i_CMP() {
	fetched_data = cpu_bus_rd(effective_addr);
	result = context.a - fetched_data;

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
	context.flags = ((int16_t)result >= 0) ? SET_FLAG_ON(FLAG_C) : SET_FLAG_OFF(FLAG_C);
}
void i_CPX() {
	fetched_data = cpu_bus_rd(effective_addr);
	result = context.x - fetched_data;

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
	context.flags = ((int16_t)result >= 0) ? SET_FLAG_ON(FLAG_C) : SET_FLAG_OFF(FLAG_C);
}
void i_CPY() {
	fetched_data = cpu_bus_rd(effective_addr);
	result = context.y - fetched_data;

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
	context.flags = ((int16_t)result >= 0) ? SET_FLAG_ON(FLAG_C) : SET_FLAG_OFF(FLAG_C);
}
void i_DEC() {
	result = cpu_bus_rd(effective_addr) - 1;
	cpu_bus_wr(effective_addr, (uint8_t)result);

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
}
void i_DEX() {
	result = --(context.x);

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
}
void i_DEY() {
	result = --(context.y);

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
}
void i_EOR() {
	fetched_data = cpu_bus_rd(effective_addr);
	result = fetched_data ^ context.a;
	context.a = (uint8_t)result;

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
}
void i_INC() {
	result = cpu_bus_rd(effective_addr) + 1;
	cpu_bus_wr(effective_addr, (uint8_t)result);

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
} 
void i_INX() {
	result = ++(context.x);

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
} 
void i_INY() {
	result = ++(context.y);

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
} 
void i_JMP() {
	context.pc = effective_addr;
}
void i_JSR() {
	result = context.pc - 1;// + 3;
	STK_PUSH(result >> 8); //high byte
	STK_PUSH(result & 0xFF); //low byte
	context.pc = effective_addr;
}
void i_LDA() {
	fetched_data = cpu_bus_rd(effective_addr);
	result = fetched_data;
	context.a = (uint8_t)result;

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
} 
void i_LDX() {
	result = cpu_bus_rd(effective_addr);
	context.x = (uint8_t)result;

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
}
void i_LDY() {
	result = cpu_bus_rd(effective_addr);
	context.y = (uint8_t)result;

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
}
void i_LSR() {
	if (opcode_table[fetched_opcode].addressing_mode == a_ACC) {
		result = context.a >> 1;
		context.flags = (context.a & FLAG_C) ? SET_FLAG_ON(FLAG_C) : SET_FLAG_OFF(FLAG_C);
		context.a = (uint8_t)result;
	}
	else {
		fetched_data = cpu_bus_rd(effective_addr);
		result = fetched_data >> 1;
		context.flags = (fetched_data & FLAG_C) ? SET_FLAG_ON(FLAG_C) : SET_FLAG_OFF(FLAG_C);
		cpu_bus_wr(effective_addr, (uint8_t)result);
	}

	context.flags = SET_FLAG_OFF(FLAG_N);
	SET_Z_FLAG((uint8_t)result);
} 
void i_NOP() {

} 
void i_ORA() {
	fetched_data = cpu_bus_rd(effective_addr);
	result = fetched_data | context.a;
	context.a = (uint8_t)result;

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
} 
void i_PHA() {
	STK_PUSH(context.a);
}
void i_PHP() {
	STK_PUSH(context.flags | FLAG_B | FLAG_UNUSED);
} 
void i_PLA() {
	STK_POP(result);
	context.a = (uint8_t)result;

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
} 
void i_PLP() {
	STK_POP(result);
	context.flags = ((uint8_t)result & ~(FLAG_UNUSED | FLAG_B)) | (context.flags & (FLAG_UNUSED | FLAG_B));

	//SET_N_FLAG(result);
	//SET_Z_FLAG((uint8_t)result);
} 
void i_ROL() {
	if (opcode_table[fetched_opcode].addressing_mode == a_ACC) {
		result = context.a;
		result <<= 1;
		result |= context.flags & FLAG_C;
		context.a = (uint8_t)result;
	}
	else {
		fetched_data = cpu_bus_rd(effective_addr);
		result = fetched_data;
		result <<= 1;
		result |= context.flags & FLAG_C;
		cpu_bus_wr(effective_addr, (uint8_t)result);
	}

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
	SET_C_FLAG(result);
}
void i_ROR() {
	if (opcode_table[fetched_opcode].addressing_mode == a_ACC) {
		result = context.a;
		result |= (result & 0x1) << 9;
		result >>= 1;
		result |= (context.flags & FLAG_C) << 7;
		context.a = (uint8_t)result;
	}
	else {
		fetched_data = cpu_bus_rd(effective_addr);
		result = fetched_data;
		result |= (result & 0x1) << 9;
		result >>= 1;
		result |= (context.flags & FLAG_C) << 7;
		cpu_bus_wr(effective_addr, (uint8_t)result);
	}

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
	SET_C_FLAG(result);
} 
void i_RTI() {
	STK_POP(result);
	context.flags = (uint8_t)result | (context.flags & (FLAG_UNUSED | FLAG_B));
	STK_POP((uint8_t)result); //low byte
	STK_POP((uint8_t)context.pc); //high byte
	context.pc = result | (context.pc << 8);
} 
void i_RTS() {
	STK_POP((uint8_t)result); //low byte
	STK_POP((uint8_t)context.pc); //high byte
	context.pc = (result & 0xFF) | (context.pc << 8);
	context.pc++; //because in JSR we push the return address - 1
} 
void i_SBC() {
	fetched_data = cpu_bus_rd(effective_addr);
	fetched_data ^= 0xFF;
	result = fetched_data + context.a + (context.flags & FLAG_C);

	SET_N_FLAG(result);
	SET_V_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
	SET_C_FLAG(result);
	
	context.a = result;
}
void i_SEC() {
	context.flags = SET_FLAG_ON(FLAG_C);
} 
void i_SED() {
	context.flags = SET_FLAG_ON(FLAG_D);
} 
void i_SEI() {
	context.flags = SET_FLAG_ON(FLAG_I);
} 
void i_STA() {
	cpu_bus_wr(effective_addr, context.a);
}
void i_STX() {
	cpu_bus_wr(effective_addr, context.x);
} 
void i_STY() {
	cpu_bus_wr(effective_addr, context.y);
} 
void i_TAX() {
	context.x = context.a;

	SET_N_FLAG(context.x);
	SET_Z_FLAG(context.x);
} 
void i_TAY() {
	context.y = context.a;

	SET_N_FLAG(context.y);
	SET_Z_FLAG(context.y);
}
void i_TSX() {
	context.x = context.sp;

	SET_N_FLAG(context.x);
	SET_Z_FLAG(context.x);
} 
void i_TXA() {
	context.a = context.x;

	SET_N_FLAG(context.a);
	SET_Z_FLAG(context.a);
} 
void i_TXS() {
	context.sp = context.x;
} 
void i_TYA() {
	context.a = context.y;

	SET_N_FLAG(context.a);
	SET_Z_FLAG(context.a);
}

void i_ALR()
{
	fetched_data = cpu_bus_rd(effective_addr);
	result = fetched_data & context.a;
	result >>= 1;
	cpu_bus_wr(effective_addr, (uint8_t)result);

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
	SET_C_FLAG(result);
}
void i_ANC()
{
	fetched_data = cpu_bus_rd(effective_addr);
	result = fetched_data & context.a;
	context.a = (uint8_t)result;

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
	SET_C_FLAG(result << 1); //bit 7 goes to carry
}
void i_ANE()
{
	fetched_data = cpu_bus_rd(effective_addr);
	result = fetched_data & context.x;
	context.a = (uint8_t)result;

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
}
void i_ARR()
{
	fetched_data = cpu_bus_rd(effective_addr);
	result = fetched_data & context.a;
	result >>= 1;
	cpu_bus_wr(effective_addr, (uint8_t)result);

	SET_N_FLAG(result);
	SET_V_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
	SET_C_FLAG(result);
}
void i_DCP()
{
	fetched_data = cpu_bus_rd(effective_addr);
	fetched_data--;
	result = fetched_data;
	cpu_bus_wr(effective_addr, (uint8_t)result);

	result = context.a - (uint8_t)result;

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
	context.flags = ((int16_t)result >= 0) ? SET_FLAG_ON(FLAG_C) : SET_FLAG_OFF(FLAG_C);
}
void i_ISC()
{
	fetched_data = cpu_bus_rd(effective_addr);
	fetched_data++;
	result = fetched_data;
	cpu_bus_wr(effective_addr, (uint8_t)result);

	fetched_data ^= 0xFF;
	result = context.a + fetched_data + (context.flags & FLAG_C);

	SET_N_FLAG(result);
	SET_V_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
	SET_C_FLAG(result);

	context.a = (uint8_t)result;
}
void i_JAM()
{
	context.pc--;
}
void i_LAS()
{
	fetched_data = cpu_bus_rd(effective_addr);
	result = fetched_data & context.sp;
	context.a = result;
	context.x = result;
	context.sp = result;

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
}
void i_LAX()
{
	fetched_data = cpu_bus_rd(effective_addr);
	result = fetched_data;
	context.a = result;
	context.x = result;

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
}
void i_RLA()
{
	fetched_data = cpu_bus_rd(effective_addr);
	result = fetched_data;
	result <<= 1;
	result |= context.flags & FLAG_C;
	cpu_bus_wr(effective_addr, (uint8_t)result);

	SET_C_FLAG(result);


	result = (uint8_t)result & context.a;
	context.a = result;

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
}
void i_RRA()
{
	fetched_data = cpu_bus_rd(effective_addr);
	result = fetched_data;
	result |= (result & 0x1) << 9;
	result >>= 1;
	result |= (context.flags & FLAG_C) << 7;
	fetched_data = result;
	cpu_bus_wr(effective_addr, (uint8_t)result);

	SET_C_FLAG(result);


	result = (uint8_t)result + context.a + (context.flags & FLAG_C);

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
	SET_V_FLAG(result);
	SET_C_FLAG(result);

	context.a = result;
}
void i_SAX()
{
	result = context.a & context.x;
	cpu_bus_wr(effective_addr, (uint8_t)result);
}
void i_SBX()
{
	fetched_data = cpu_bus_rd(effective_addr);
	result = context.a & context.x - fetched_data;
	context.x = result;

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
	context.flags = ((int16_t)result >= 0) ? SET_FLAG_ON(FLAG_C) : SET_FLAG_OFF(FLAG_C);
}
void i_SHA()
{
	fetched_data = cpu_bus_rd(effective_addr + 1);
	result = context.a & context.x & fetched_data;
	cpu_bus_wr(effective_addr, (uint8_t)result);
}
void i_SHY()
{
	fetched_data = cpu_bus_rd(effective_addr + 1);
	result = context.y & fetched_data;
	cpu_bus_wr(effective_addr, (uint8_t)result);
}
void i_SHX()
{
	fetched_data = cpu_bus_rd(effective_addr + 1);
	result = context.x & fetched_data;
	cpu_bus_wr(effective_addr, (uint8_t)result);
}
void i_SLO()
{
	fetched_data = cpu_bus_rd(effective_addr); 
	result = fetched_data << 1;
	cpu_bus_wr(effective_addr, (uint8_t)result);

	SET_C_FLAG(result);

	result = context.a | (uint8_t)result;
	context.a = result;

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
}
void i_SRE()
{
	fetched_data = cpu_bus_rd(effective_addr);
	result = fetched_data >> 1;
	context.flags = (fetched_data & FLAG_C) ? SET_FLAG_ON(FLAG_C) : SET_FLAG_OFF(FLAG_C);
	cpu_bus_wr(effective_addr, (uint8_t)result);

	result = context.a ^ (uint8_t)result;
	context.a = result;

	SET_N_FLAG(result);
	SET_Z_FLAG((uint8_t)result);
}
void i_TAS()
{
	context.sp = context.a & context.x;

	fetched_data = cpu_bus_rd(effective_addr + 1);
	result = context.sp & fetched_data;
	cpu_bus_wr(effective_addr, (uint8_t)result);
}


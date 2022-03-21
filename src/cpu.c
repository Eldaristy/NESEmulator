#include "../include/cpu.h"

opcode opcode_table[0x100] = {
	{i_BRK,a_IMP}, {i_ORA,a_XND}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {i_ORA,a_ZPG}, {i_ASL,a_ZPG}, {x_XXX,x_XXX}, {i_PHP,a_IMP}, {i_ORA,a_IMM}, {i_ASL,a_ACC}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {i_ORA,a_ABS}, {i_ASL,a_ABS}, {x_XXX,x_XXX},
	{i_BPL,a_REL}, {i_ORA,a_INY}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {i_ORA,a_ZPX}, {i_ASL,a_ZPX}, {x_XXX,x_XXX}, {i_CLC,a_IMP}, {i_ORA,a_ABY}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {i_ORA,a_ABX}, {i_ASL,a_ABX}, {x_XXX,x_XXX},
	{i_JSR,a_ABS}, {i_AND,a_XND}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {i_BIT,a_ZPG}, {i_AND,a_ZPG}, {i_ROL,a_ZPG}, {x_XXX,x_XXX}, {i_PLP,a_IMP}, {i_AND,a_IMM}, {i_ROL,a_ACC}, {x_XXX,x_XXX}, {i_BIT,a_ABS}, {i_AND,a_ABS}, {i_ROL,a_ABS}, {x_XXX,x_XXX},
	{i_BMI,a_REL}, {i_AND,a_INY}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {i_AND,a_ZPX}, {i_ROL,a_ZPX}, {x_XXX,x_XXX}, {i_SEC,a_IMP}, {i_AND,a_ABY}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {i_AND,a_ABX}, {i_ROL,a_ABX}, {x_XXX,x_XXX},
	{i_RTI,a_IMP}, {i_EOR,a_XND}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {i_EOR,a_ZPG}, {i_LSR,a_ZPG}, {x_XXX,x_XXX}, {i_PHA,a_IMP}, {i_EOR,a_IMM}, {i_LSR,a_ACC}, {x_XXX,x_XXX}, {i_JMP,a_ABS}, {i_EOR,a_ABS}, {i_LSR,a_ABS}, {x_XXX,x_XXX},
	{i_BVC,a_REL}, {i_EOR,a_INY}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {i_EOR,a_ZPX}, {i_LSR,a_ZPX}, {x_XXX,x_XXX}, {i_CLI,a_IMP}, {i_EOR,a_ABY}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {i_EOR,a_ABX}, {i_LSR,a_ABX}, {x_XXX,x_XXX},
	{i_RTS,a_IMP}, {i_ADC,a_XND}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {i_ADC,a_ZPG}, {i_ROR,a_ZPG}, {x_XXX,x_XXX}, {i_PLA,a_IMP}, {i_ADC,a_IMM}, {i_ROR,a_ACC}, {x_XXX,x_XXX}, {i_JMP,a_IND}, {i_ADC,a_ABS}, {i_ROR,a_ABS}, {x_XXX,x_XXX},
	{i_BVS,a_REL}, {i_ADC,a_INY}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {i_ADC,a_ZPX}, {i_ROR,a_ZPX}, {x_XXX,x_XXX}, {i_SEI,a_IMP}, {i_ADC,a_ABY}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {i_ADC,a_ABX}, {i_ROR,a_ABX}, {x_XXX,x_XXX},
	{x_XXX,x_XXX}, {i_STA,a_XND}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {i_STY,a_ZPG}, {i_STA,a_ZPG}, {i_STX,a_ZPG}, {x_XXX,x_XXX}, {i_DEY,a_IMP}, {x_XXX,x_XXX}, {i_TXA,a_IMP}, {x_XXX,x_XXX}, {i_STY,a_ABS}, {i_STA,a_ABS}, {i_STX,a_ABS}, {x_XXX,x_XXX},
	{i_BCC,a_REL}, {i_STA,a_INY}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {i_STY,a_ZPX}, {i_STA,a_ZPX}, {i_STX,a_ZPY}, {x_XXX,x_XXX}, {i_TYA,a_IMP}, {i_STA,a_ABY}, {i_TXS,a_IMP}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {i_STA,a_ABX}, {x_XXX,x_XXX}, {x_XXX,x_XXX},
	{i_LDY,a_IMM}, {i_LDA,a_XND}, {i_LDX,a_IMM}, {x_XXX,x_XXX}, {i_LDY,a_ZPG}, {i_LDA,a_ZPG}, {i_LDX,a_ZPG}, {x_XXX,x_XXX}, {i_TAY,a_IMP}, {i_LDA,a_IMM}, {i_TAX,a_IMP}, {x_XXX,x_XXX}, {i_LDY,a_ABS}, {i_LDA,a_ABS}, {i_LDX,a_ABS}, {x_XXX,x_XXX},
	{i_BCS,a_REL}, {i_LDA,a_INY}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {i_LDY,a_ZPX}, {i_LDA,a_ZPX}, {i_LDX,a_ZPY}, {x_XXX,x_XXX}, {i_CLV,a_IMP}, {i_LDA,a_ABY}, {i_TSX,a_IMP}, {x_XXX,x_XXX}, {i_LDY,a_ABX}, {i_LDA,a_ABX}, {i_LDX,a_ABY}, {x_XXX,x_XXX},
	{i_CPY,a_IMM}, {i_CMP,a_XND}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {i_CPY,a_ZPG}, {i_CMP,a_ZPG}, {i_DEC,a_ZPG}, {x_XXX,x_XXX}, {a_INY,a_IMP}, {i_CMP,a_IMM}, {i_DEX,a_IMP}, {x_XXX,x_XXX}, {i_CPY,a_ABS}, {i_CMP,a_ABS}, {i_DEC,a_ABS}, {x_XXX,x_XXX},
	{i_BNE,a_REL}, {i_CMP,a_INY}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {i_CMP,a_ZPX}, {i_DEC,a_ZPX}, {x_XXX,x_XXX}, {i_CLD,a_IMP}, {i_CMP,a_ABY}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {i_CMP,a_ABX}, {i_DEC,a_ABX}, {x_XXX,x_XXX},
	{i_CPX,a_IMM}, {i_SBC,a_XND}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {i_CPX,a_ZPG}, {i_SBC,a_ZPG}, {i_INC,a_ZPG}, {x_XXX,x_XXX}, {i_INX,a_IMP}, {i_SBC,a_IMM}, {i_NOP,a_IMP}, {x_XXX,x_XXX}, {i_CPX,a_ABS}, {i_SBC,a_ABS}, {i_INC,a_ABS}, {x_XXX,x_XXX},
	{i_BEQ,a_REL}, {i_SBC,a_INY}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {i_SBC,a_ZPX}, {i_INC,a_ZPX}, {x_XXX,x_XXX}, {i_SED,a_IMP}, {i_SBC,a_ABY}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {x_XXX,x_XXX}, {i_SBC,a_ABX}, {i_INC,a_ABX}, {x_XXX,x_XXX}
};

uint8_t run_clock()
{
	effective_addr = 0;
	fetched_opcode = 0;
	fetched_data = 0;

	while(1) {
		fetched_opcode = cpu_bus_rd(context.pc);
		opcode_table[fetched_opcode].addressing_mode();
	}
}
void a_ACC()
{
	fetched_data = context.a;
}
void a_ABS()
{
	effective_addr = cpu_bus_rd(context.pc + 1); //low byte read from lower address
	effective_addr += cpu_bus_rd(context.pc + 2) << 8; //high byte read from higher address
	fetched_data = cpu_bus_rd(effective_addr);
}
void a_ABX()
{
	effective_addr = cpu_bus_rd(context.pc + 1); //low byte read from lower address
	effective_addr += cpu_bus_rd(context.pc + 2) << 8; //high byte read from higher address
	effective_addr += context.x;
	fetched_data = cpu_bus_rd(effective_addr);
}
void a_ABY()
{
	effective_addr = cpu_bus_rd(context.pc + 1); //low byte read from lower address
	effective_addr += cpu_bus_rd(context.pc + 2) << 8; //high byte read from higher address
	effective_addr += context.y;
	fetched_data = cpu_bus_rd(effective_addr);
}
void a_IMM()
{
	effective_addr = context.pc + 1;
	fetched_data = cpu_bus_rd(effective_addr);
}
void a_IMP()
{
}
void a_IND() 
{
	effective_addr = cpu_bus_rd(context.pc + 1);
	effective_addr += cpu_bus_rd(context.pc + 2) << 8;
	effective_addr = cpu_bus_rd(effective_addr);
	fetched_data = 0;
}
void a_INY() 
{
	effective_addr = cpu_bus_rd(context.pc + 1);
	effective_addr += cpu_bus_rd(context.pc + 2) << 8;
	effective_addr = cpu_bus_rd(effective_addr);
	effective_addr += context.y;
	fetched_data = 0;
}
void a_XND()
{
	effective_addr = (cpu_bus_rd(context.pc + 1) + context.x) & 0xFF; //without carry
	effective_addr = cpu_bus_rd(effective_addr);
	effective_addr += cpu_bus_rd((effective_addr + 1) & 0xFF) << 8; //emulate the 0xFF wrapping around bug
	effective_addr = cpu_bus_rd(effective_addr);
	fetched_data = 0;
}
void a_REL()
{
	effective_addr = context.pc;
	effective_addr += (int8_t)cpu_bus_rd(context.pc + 1);
	fetched_data = 0;
}
void a_ZPG() 
{
	effective_addr = cpu_bus_rd(context.pc + 1);
	fetched_data = cpu_bus_rd(effective_addr);
}
void a_ZPX() 
{
	uint8_t effective_addr = 0; //since it's zero-paged, it's only 8 bits
	effective_addr = cpu_bus_rd(context.pc + 1);
	effective_addr += context.x;
	effective_addr &= 0xFF;
	fetched_data = cpu_bus_rd(effective_addr);
}
void a_ZPY()
{
	uint8_t effective_addr = 0; //since it's zero-paged, it's only 8 bits
	effective_addr = cpu_bus_rd(context.pc + 1);
	effective_addr += context.y;
	effective_addr &= 0xFF;
	fetched_data = cpu_bus_rd(effective_addr);
}

//instructions
void i_ADC()
{
	result = fetched_data + (context.flags & FLAG_C);	
	context.a += result;

	SET_N_FLAG(result);
	SET_Z_FLAG(result);
	SET_C_FLAG(result);
	SET_V_FLAG(result);
}
void i_AND()
{
	result = fetched_data & context.a;
	context.a = (uint8_t)result;

	SET_N_FLAG(result);
	SET_Z_FLAG(result);
}
void i_ASL()
{
	if(opcode_table[fetched_opcode].addressing_mode == a_ACC) {
		result = context.a << 1;
		context.a = (uint8_t)result;
	}
	else {
		result = fetched_data << 1;
		cpu_bus_wr(effective_addr, (uint8_t)result);
	}

	SET_N_FLAG(result);
	SET_Z_FLAG(result);
	SET_C_FLAG(result);
}
void i_BCC()
{
	if (!(context.flags & FLAG_C)) {
		context.pc = effective_addr;
	}
}
void i_BCS() {
	if (context.flags & FLAG_C) {
		context.pc = effective_addr;
	}
} 
void i_BEQ() {
	if (context.flags & FLAG_Z) {
		context.pc = effective_addr;
	}
}
void i_BIT() {
	result = fetched_data & context.a;

	SET_N_FLAG(result);
	SET_Z_FLAG(result);
	SET_V_FLAG(result);
}
void i_BMI() {
	if (context.flags & FLAG_N) {
		context.pc = effective_addr;
	}
}
void i_BNE() {
	if (!(context.flags & FLAG_Z)) {
		context.pc = effective_addr;
	}
}
void i_BPL() {
	if (!(context.flags & FLAG_N)) {
		context.pc = effective_addr;
	}
}
void i_BRK() {
	assert(!"not implemented");
	context.flags = SET_FLAG_ON(FLAG_I);
}
void i_BVC() {
	if (!(context.flags & FLAG_V)) {
		context.pc = effective_addr;
	}
}
void i_BVS() {
	if (context.flags & FLAG_V) {
		context.pc = effective_addr;
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
	result = context.a - fetched_data;

	SET_N_FLAG(result);
	SET_Z_FLAG(result);
	SET_C_FLAG(result);
}
void i_CPX() {
	result = context.x - fetched_data;

	SET_N_FLAG(result);
	SET_Z_FLAG(result);
	SET_C_FLAG(result);
}
void i_CPY() {
	result = context.y - fetched_data;

	SET_N_FLAG(result);
	SET_Z_FLAG(result);
	SET_C_FLAG(result);
}
void i_DEC() {
	result = cpu_bus_rd(effective_addr) - 1;
	cpu_bus_wr(effective_addr, (uint8_t)result);

	SET_N_FLAG(result);
	SET_Z_FLAG(result);
}
void i_DEX() {
	result = --(context.x);

	SET_N_FLAG(result);
	SET_Z_FLAG(result);
}
void i_DEY() {
	result = --(context.y);

	SET_N_FLAG(result);
	SET_Z_FLAG(result);
}
void i_EOR() {
	result = fetched_data ^ context.a;
	context.a = (uint8_t)result;

	SET_N_FLAG(result);
	SET_Z_FLAG(result);
}
void i_INC() {
	result = cpu_bus_rd(effective_addr) + 1;
	cpu_bus_wr(effective_addr, (uint8_t)result);

	SET_N_FLAG(result);
	SET_Z_FLAG(result);
} 
void i_INX() {
	result = ++(context.x);

	SET_N_FLAG(result);
	SET_Z_FLAG(result);
} 
void i_INY() {
	result = ++(context.y);

	SET_N_FLAG(result);
	SET_Z_FLAG(result);
} 
void i_JMP() {
	context.pc = effective_addr;
}
void i_JSR() {
	result = context.pc + 3;
	STK_PUSH(result >> 8); //high byte
	STK_PUSH(result & 0xFF); //low byte
	context.pc = effective_addr;
}
void i_LDA() {
	result = cpu_bus_rd(effective_addr);
	context.a = (uint8_t)result;

	SET_N_FLAG(result);
	SET_Z_FLAG(result);
} 
void i_LDX() {
	result = cpu_bus_rd(effective_addr);
	context.x = (uint8_t)result;

	SET_N_FLAG(result);
	SET_Z_FLAG(result);
}
void i_LDY() {
	result = cpu_bus_rd(effective_addr);
	context.y = (uint8_t)result;

	SET_N_FLAG(result);
	SET_Z_FLAG(result);
}
void i_LSR() {
	if (opcode_table[fetched_opcode].addressing_mode == a_ACC) {
		result = context.a >> 1;
		context.a = (uint8_t)result;
	}
	else {
		result = fetched_data >> 1;
		cpu_bus_wr(effective_addr, (uint8_t)result);
	}

	context.flags = SET_FLAG_OFF(FLAG_N);
	SET_Z_FLAG(result);
	SET_C_FLAG(result);
} 
void i_NOP() {

} 
void i_ORA() {
	result = fetched_data | context.a;
	context.a = (uint8_t)result;

	SET_N_FLAG(result);
	SET_Z_FLAG(result);
} 
void i_PHA() {
	STK_PUSH(context.a);
}
void i_PHP() {
	STK_PUSH(context.flags);
} 
void i_PLA() {
	STK_POP(result);
	context.a = (uint8_t)result;

	SET_N_FLAG(result);
	SET_Z_FLAG(result);
} 
void i_PLP() {
	STK_POP(result);
	context.flags = (uint8_t)result;

	SET_N_FLAG(result);
	SET_Z_FLAG(result);
} 
void i_ROL() {
	if (opcode_table[fetched_opcode].addressing_mode == a_ACC) {
		result = context.a;
		result <<= 1;
		result |= context.flags & FLAG_C;
		context.a = (uint8_t)result;
	}
	else {
		result = fetched_data;
		result <<= 1;
		result |= context.flags & FLAG_C;
		cpu_bus_wr(effective_addr, (uint8_t)result);
	}

	SET_N_FLAG(result);
	SET_Z_FLAG(result);
	SET_C_FLAG(result);
}
void i_ROR() {
	if (opcode_table[fetched_opcode].addressing_mode == a_ACC) {
		result = context.a;
		result |= result & 0x1 << 9;
		result >>= 1;
		result |= context.flags & FLAG_C << 7;
		context.a = (uint8_t)result;
	}
	else {
		result = fetched_data;
		result |= result & 0x1 << 9;
		result >>= 1;
		result |= context.flags & FLAG_C << 7;
		cpu_bus_wr(effective_addr, (uint8_t)result);
	}

	SET_N_FLAG(result);
	SET_Z_FLAG(result);
	SET_C_FLAG(result);
} 
void i_RTI() {
	assert(!"not implemented");
} 
void i_RTS() {
	assert(!"not implemented");
} 
void i_SBC() {
	assert(!"not implemented");
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

void x_XXX()
{

}

#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include "cpu_bus.h"

static uint8_t set_flags(uint16_t); //recieves uint16_t and not uint8_t in order to handle 8-bit overflows 

/*
The context of the 6502 microprocessor - all of its registers
*/
typedef struct {
	uint8_t a; // Accumulator
	uint8_t x; // X Index
	uint8_t y; // Y Index
	uint8_t sp; // Stack Pointer
	uint16_t pc; // Program Counter
	uint8_t flags; // Status Register
} cpu_context;

#define FLAG_C (1 << 0) // Carry
#define FLAG_Z (1 << 1) // Zero
#define FLAG_I (1 << 2) // Interrupt Disable
#define FLAG_D (1 << 3) // Decimal
#define FLAG_B (1 << 4) // B
#define FLAG_UNUSED (1 << 5)
#define FLAG_V (1 << 6) // Overflow
#define FLAG_N (1 << 7) //Negative

static cpu_context context;
static uint16_t effective_addr;
static uint8_t fetched_opcode;
static uint8_t fetched_data; 
static uint16_t result;

#define STK_PUSH(x) cpu_bus_wr((--context.sp | 0x100) + 1, x)
#define STK_POP(x) x = cpu_bus_rd((context.sp++ | 0x100 + 1))					


#define SET_FLAG_ON(f) (context.flags | f)
#define SET_FLAG_OFF(f) (context.flags & ~f)

//the flags are checked and set in the end of the instructions
#define SET_C_FLAG(x) context.flags = (x & 0x100) ? SET_FLAG_ON(FLAG_C) : SET_FLAG_OFF(FLAG_C)
#define SET_Z_FLAG(x) context.flags = (!x) ? SET_FLAG_ON(FLAG_Z) : SET_FLAG_OFF(FLAG_Z)
#define SET_I_FLAG(x) 
#define SET_D_FLAG(x) 
#define SET_B_FLAG(x) 
#define SET_V_FLAG(x) context.flags = ((~(context.a ^ fetched_data) ^ x) & 0x80) ? SET_FLAG_ON(FLAG_V) : SET_FLAG_OFF(FLAG_Z)	  
#define SET_N_FLAG(x) context.flags = (x & 0x80) ? SET_FLAG_ON(FLAG_N) : SET_FLAG_OFF(FLAG_N)

typedef struct {
	void (*instruction)();
	void (*addressing_mode)();
} opcode;

static opcode opcode_table[0x100];

/* 
Addressing modes - "a" stands for addresing
*/
void a_ACC();
void a_ABS(); void a_ABX(); void a_ABY();
void a_IMM();
void a_IMP();
void a_IND(); void a_INY(); void a_XND();
void a_REL();
void a_ZPG(); void a_ZPX(); void a_ZPY();

/*
Instructions - "i" stands for instruction 
*/
void i_ADC(); void i_AND(); void i_ASL(); void i_BCC();
void i_BCS(); void i_BEQ(); void i_BIT(); void i_BMI();
void i_BNE(); void i_BPL(); void i_BRK(); void i_BVC();
void i_BVS(); void i_CLC(); void i_CLD(); void i_CLI();
void i_CLV(); void i_CMP(); void i_CPX(); void i_CPY();
void i_DEC(); void i_DEX(); void i_DEY(); void i_EOR();
void i_INC(); void i_INX(); void i_INY(); void i_JMP();
void i_JSR(); void i_LDA(); void i_LDX(); void i_LDY();
void i_LSR(); void i_NOP(); void i_ORA(); void i_PHA();
void i_PHP(); void i_PLA(); void i_PLP(); void i_ROL();
void i_ROR(); void i_RTI(); void i_RTS(); void i_SBC();
void i_SEC(); void i_SED(); void i_SEI(); void i_STA();
void i_STX(); void i_STY(); void i_TAX(); void i_TAY();
void i_TSX(); void i_TXA(); void i_TXS(); void i_TYA();


void x_XXX(); // all illegal opcodes



uint8_t run_clock();

#endif
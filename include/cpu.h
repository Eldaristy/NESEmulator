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

#define FLAG_C 1 << 0 // Carry
#define FLAG_Z 1 << 1 // Zero
#define FLAG_I 1 << 2 // Interrupt Disable
#define FLAG_D 1 << 3 // Decimal
#define FLAG_B 1 << 4 // B
#define FLAG_UNUSED 1 << 5
#define FLAG_V 1 << 6 // Overflow
#define FLAG_N 1 << 7 //Negative

extern cpu_context context;
static uint16_t effective_addr;
static uint8_t fetched_opcode;
static uint8_t fetched_data; 
static uint16_t result;

#define STK_PUSH(x) cpu_bus_wr((--context.sp | 0x100) + 1, x)
#define STK_POP(x) x = cpu_bus_rd((context.sp++ | 0x100 + 1))					


#define SET_FLAG_ON(f) context.flags | f
#define SET_FLAG_OFF(f) context.flags & ~f

//the flags are checked and set in the end of the instructions
#define SET_C_FLAG(x) context.flags = (x & 0x100) ? SET_FLAG_ON(FLAG_C) : SET_FLAG_OFF(FLAG_C)
#define SET_Z_FLAG(x) context.flags = (!x) ? SET_FLAG_ON(FLAG_Z) : SET_FLAG_OFF(FLAG_Z)
#define SET_I_FLAG(x) 
#define SET_D_FLAG(x) 
#define SET_B_FLAG(x) 
#define SET_V_FLAG(x) context.flags = ((~(context.a ^ fetched_data) ^ x) & 0x80) ? SET_FLAG_ON(FLAG_V) : SET_FLAG_OFF(FLAG_Z)	  
#define SET_N_FLAG(x) context.flags = (x & 0x80) ? SET_FLAG_ON(FLAG_N) : SET_FLAG_OFF(FLAG_N)

typedef struct {
	uint8_t (*instruction)();
	uint8_t (*addressing_mode)();
} opcode;

static opcode opcode_table[0x100];

/* 
Addressing modes - "a" stands for addresing
*/
uint8_t a_ACC();
uint8_t a_ABS(); uint8_t a_ABX(); uint8_t a_ABY();
uint8_t a_IMM();
uint8_t a_IMP();
uint8_t a_IND(); uint8_t a_INY(); uint8_t a_XND();
uint8_t a_REL();
uint8_t a_ZPG(); uint8_t a_ZPX(); uint8_t a_ZPY();

/*
Instructions - "i" stands for instruction 
*/
uint8_t i_ADC(); uint8_t i_AND(); uint8_t i_ASL(); uint8_t i_BCC();
uint8_t i_BCS(); uint8_t i_BEQ(); uint8_t i_BIT(); uint8_t i_BMI();
uint8_t i_BNE(); uint8_t i_BPL(); uint8_t i_BRK(); uint8_t i_BVC();
uint8_t i_BVS(); uint8_t i_CLC(); uint8_t i_CLD(); uint8_t i_CLI();
uint8_t i_CLV(); uint8_t i_CMP(); uint8_t i_CPX(); uint8_t i_CPY();
uint8_t i_DEC(); uint8_t i_DEX(); uint8_t i_DEY(); uint8_t i_EOR();
uint8_t i_INC(); uint8_t i_INX(); uint8_t i_INY(); uint8_t i_JMP();
uint8_t i_JSR(); uint8_t i_LDA(); uint8_t i_LDX(); uint8_t i_LDY();
uint8_t i_LSR(); uint8_t i_NOP(); uint8_t i_ORA(); uint8_t i_PHA();
uint8_t i_PHP(); uint8_t i_PLA(); uint8_t i_PLP(); uint8_t i_ROL();
uint8_t i_ROR(); uint8_t i_RTI(); uint8_t i_RTS(); uint8_t i_SBC();
uint8_t i_SEC(); uint8_t i_SED(); uint8_t i_SEI(); uint8_t i_STA();
uint8_t i_STX(); uint8_t i_STY(); uint8_t i_TAX(); uint8_t i_TAY();
uint8_t i_TSX(); uint8_t i_TXA(); uint8_t i_TXS(); uint8_t i_TYA();

uint8_t x_XXX(); // all illegal opcodes -
// "x" is just to fit the name pattern of other addressing modes and instrucitons functions


uint8_t run_clock();

#endif
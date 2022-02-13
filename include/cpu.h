#ifndef CPU_H
#define CPU_H

#include <stdint.h>

/*
The context of the 6502 microprocessor - all of its registers
*/
typedef struct {
	uint8_t a; // Accumulator
	uint8_t x; // X Index
	uint8_t y; // Y Index
	uint8_t sp; // Stack Pointer
	uint16_t pc; // Program Counter

	/* Flags Register */
	uint8_t f_n : 1; // Negative 
	uint8_t f_v : 1; // Overflow 
	uint8_t f_UNUSED : 1;
	uint8_t f_b : 1; // B 
	uint8_t f_d : 1; // Decimal 
	uint8_t f_i : 1; // Interrupt Disable
	uint8_t f_z : 1; // Zero
	uint8_t f_c : 1; // Carry
} cpu_context;

extern cpu_context context;

typedef struct {
	uint8_t* instruction;
	uint8_t* addressing_mode;
} opcode;

/* 
Addressing modes 
*/
uint8_t ACC();
uint8_t ABS(); uint8_t ABX(); uint8_t ABY();
uint8_t IMM();
uint8_t IMP();
uint8_t IND(); uint8_t INY(); uint8_t XND();
uint8_t REL();
uint8_t ZPG(); uint8_t ZPX(); uint8_t ZPY();

/*
Instructions
*/
uint8_t ADC(); uint8_t AND(); uint8_t ASL(); uint8_t BCC();
uint8_t BCS(); uint8_t BEQ(); uint8_t BIT(); uint8_t BMI();
uint8_t BNE(); uint8_t BPL(); uint8_t BRK(); uint8_t BVC();
uint8_t BVS(); uint8_t CLC(); uint8_t CLD(); uint8_t CLI();
uint8_t CLV(); uint8_t CMP(); uint8_t CPX(); uint8_t CPY();
uint8_t DEC(); uint8_t DEX(); uint8_t DEY(); uint8_t EOR();
uint8_t INC(); uint8_t INX(); uint8_t INY(); uint8_t JMP();
uint8_t JSR(); uint8_t LDA(); uint8_t LDX(); uint8_t LDY();
uint8_t LSR(); uint8_t NOP(); uint8_t ORA(); uint8_t PHA();
uint8_t PHP(); uint8_t PLA(); uint8_t PLP(); uint8_t ROL();
uint8_t ROR(); uint8_t RTI(); uint8_t RTS(); uint8_t SBC();
uint8_t SEC(); uint8_t SED(); uint8_t SEI(); uint8_t STA();
uint8_t STX(); uint8_t STY(); uint8_t TAX(); uint8_t TAY();
uint8_t TSX(); uint8_t TXA(); uint8_t TXS(); uint8_t TYA();

uint8_t XXX(); // all illegal opcodes

#endif
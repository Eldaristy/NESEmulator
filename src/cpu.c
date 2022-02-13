#include "../include/cpu.h"

opcode instruction_set[0x100] = {
	{BRK,IMP}, {ORA,XND}, {XXX,XXX}, {XXX,XXX}, {XXX,XXX}, {ORA,ZPG}, {ASL,ZPG}, {XXX,XXX}, {PHP,IMP}, {ORA,IMM}, {ASL,ACC}, {XXX,XXX}, {XXX,XXX}, {ORA,ABS}, {ASL,ABS}, {XXX,XXX},
	{BPL,REL}, {ORA,INY}, {XXX,XXX}, {XXX,XXX}, {XXX,XXX}, {ORA,ZPX}, {ASL,ZPX}, {XXX,XXX}, {CLC,IMP}, {ORA,ABY}, {XXX,XXX}, {XXX,XXX}, {XXX,XXX}, {ORA,ABX}, {ASL,ABX}, {XXX,XXX},
	{JSR,ABS}, {AND,XND}, {XXX,XXX}, {XXX,XXX}, {BIT,ZPG}, {AND,ZPG}, {ROL,ZPG}, {XXX,XXX}, {PLP,IMP}, {AND,IMM}, {ROL,ACC}, {XXX,XXX}, {BIT,ABS}, {AND,ABS}, {ROL,ABS}, {XXX,XXX},
	{BMI,REL}, {AND,INY}, {XXX,XXX}, {XXX,XXX}, {XXX,XXX}, {AND,ZPG}, {ROL,ZPG}, {XXX,XXX}, {SEC,IMP}, {AND,ABY}, {XXX,XXX}, {XXX,XXX}, {XXX,XXX}, {AND,ABX}, {ROL,ABX}, {XXX,XXX},
	{RTI,IMP}, {EOR,XND}, {XXX,XXX}, {XXX,XXX}, {XXX,XXX}, {EOR,ZPG}, {LSR,ZPG}, {XXX,XXX}, {PHA,IMP}, {EOR,IMM}, {LSR,ACC}, {XXX,XXX}, {JMP,ABS}, {EOR,ABS}, {LSR,ABS}, {XXX,XXX},
	{BVC,REL}, {EOR,INY}, {XXX,XXX}, {XXX,XXX}, {XXX,XXX}, {EOR,ZPG}, {LSR,ZPG}, {XXX,XXX}, {CLI,IMP}, {EOR,ABY}, {XXX,XXX}, {XXX,XXX}, {XXX,XXX}, {EOR,ABX}, {LSR,ABX}, {XXX,XXX},
	{RTS,IMP}, {ADC,XND}, {XXX,XXX}, {XXX,XXX}, {XXX,XXX}, {ADC,ZPG}, {ROR,ZPG}, {XXX,XXX}, {PLA,IMP}, {ADC,IMM}, {ROR,ACC}, {XXX,XXX}, {JMP,IND}, {ADC,ABS}, {ROR,ABS}, {XXX,XXX},
	{BVS,REL}, {ADC,INY}, {XXX,XXX}, {XXX,XXX}, {XXX,XXX}, {ADC,ZPG}, {ROR,ZPG}, {XXX,XXX}, {SEI,IMP}, {ADC,ABY}, {XXX,XXX}, {XXX,XXX}, {XXX,XXX}, {ADC,ABX}, {ROR,ABX}, {XXX,XXX},
	{XXX,XXX}, {STA,XND}, {XXX,XXX}, {XXX,XXX}, {STY,ZPG}, {STA,ZPG}, {STX,ZPG}, {XXX,XXX}, {DEY,IMP}, {XXX,XXX}, {TXA,IMP}, {XXX,XXX}, {STY,ABS}, {STA,ABS}, {STX,ABS}, {XXX,XXX},
	{BCC,REL}, {STA,INY}, {XXX,XXX}, {XXX,XXX}, {STY,ZPG}, {STA,ZPG}, {STX,ZPG}, {XXX,XXX}, {TYA,IMP}, {STA,ABY}, {TXS,IMP}, {XXX,XXX}, {XXX,XXX}, {STA,ABX}, {XXX,XXX}, {XXX,XXX},
	{LDY,IMM}, {LDA,XND}, {LDX,IMM}, {XXX,XXX}, {LDY,ZPG}, {LDA,ZPG}, {LDX,ZPG}, {XXX,XXX}, {TAY,IMP}, {LDA,IMM}, {TAX,IMP}, {XXX,XXX}, {LDY,ABS}, {LDA,ABS}, {LDX,ABS}, {XXX,XXX},
	{BCS,REL}, {LDA,INY}, {XXX,XXX}, {XXX,XXX}, {LDY,ZPG}, {LDA,ZPG}, {LDX,ZPG}, {XXX,XXX}, {CLV,IMP}, {LDA,ABY}, {TSX,IMP}, {XXX,XXX}, {LDY,ABX}, {LDA,ABX}, {LDX,ABY}, {XXX,XXX},
	{CPY,IMM}, {CMP,XND}, {XXX,XXX}, {XXX,XXX}, {CPY,ZPG}, {CMP,ZPG}, {DEC,ZPG}, {XXX,XXX}, {INY,IMP}, {CMP,IMM}, {DEX,IMP}, {XXX,XXX}, {CPY,ABS}, {CMP,ABS}, {DEC,ABS}, {XXX,XXX},
	{BNE,REL}, {CMP,INY}, {XXX,XXX}, {XXX,XXX}, {XXX,XXX}, {CMP,ZPG}, {DEC,ZPG}, {XXX,XXX}, {CLD,IMP}, {CMP,ABY}, {XXX,XXX}, {XXX,XXX}, {XXX,XXX}, {CMP,ABX}, {DEC,ABX}, {XXX,XXX},
	{CPX,IMM}, {SBC,XND}, {XXX,XXX}, {XXX,XXX}, {CPX,ZPG}, {SBC,ZPG}, {INC,ZPG}, {XXX,XXX}, {INX,IMP}, {SBC,IMM}, {NOP,IMP}, {XXX,XXX}, {CPX,ABS}, {SBC,ABS}, {INC,ABS}, {XXX,XXX},
	{BEQ,REL}, {SBC,INY}, {XXX,XXX}, {XXX,XXX}, {XXX,XXX}, {SBC,ZPG}, {INC,ZPG}, {XXX,XXX}, {SED,IMP}, {SBC,ABY}, {XXX,XXX}, {XXX,XXX}, {XXX,XXX}, {SBC,ABX}, {INC,ABX}, {XXX,XXX}
};

uint8_t ACC()
{
	return 0;
}
uint8_t ABS()
{
	return 0;
}
uint8_t ABX()
{
	return 0;
}
uint8_t ABY()
{
	return 0;
}
uint8_t IMM()
{
	return 0;
}
uint8_t IMP()
{
	return 0;
}
uint8_t IND() 
{
	return 0;
}
uint8_t INY() 
{
	return 0;
}
uint8_t XND()
{
	return 0;
}
uint8_t REL()
{
	return 0;
}
uint8_t ZPG() 
{
	return 0;
}
uint8_t ZPX() 
{
	return 0;
}
uint8_t ZPY()
{
	return 0;
}
	#include "../include/cpu.h"

opcode opcode_table[0x100] = {
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
//The addressing methods return the data read from the register, NULL if there isn't any register
uint8_t ACC()
{
	return context.a;
}
uint8_t ABS()
{
	effective_addr = cpu_bus_rd(context.pc + 1); //low byte read from lower address
	effective_addr += cpu_bus_rd(context.pc + 2) << 8; //high byte read from higher address
	fetched_data = cpu_bus_rd(effective_addr);
	return NULL;
}
uint8_t ABX()
{
	effective_addr = cpu_bus_rd(context.pc + 1); //low byte read from lower address
	effective_addr += cpu_bus_rd(context.pc + 2) << 8; //high byte read from higher address
	effective_addr += context.x;
	fetched_data = cpu_bus_rd(effective_addr);
	return NULL;
}
uint8_t ABY()
{
	effective_addr = cpu_bus_rd(context.pc + 1); //low byte read from lower address
	effective_addr += cpu_bus_rd(context.pc + 2) << 8; //high byte read from higher address
	effective_addr += context.y;
	fetched_data = cpu_bus_rd(effective_addr);
	return NULL;
}
uint8_t IMM()
{
	fetched_data = cpu_bus_rd(context.pc + 1);
	return NULL;
}
uint8_t IMP()
{
	return NULL;
}
uint8_t IND() 
{
	effective_addr = cpu_bus_rd(context.pc + 1);
	effective_addr += cpu_bus_rd(context.pc + 2) << 8;
	effective_addr = cpu_bus_rd(effective_addr);
	fetched_data = 0;
	return NULL;
}
uint8_t INY() 
{
	return 0;
}
uint8_t XND()
{
	effective_addr = (cpu_bus_rd(context.pc + 1) + context.x) & 0xFF; //without carry
	effective_addr = cpu_bus_rd(effective_addr);
	effective_addr += cpu_bus_rd((effective_addr + 1) & 0xFF) << 8; //emulate the 0xFF wrapping around bug
	effective_addr = cpu_bus_rd(effective_addr);
	fetched_data = 0;
	return NULL;
}
uint8_t REL()
{
	return 0;
}
uint8_t ZPG() 
{
	effective_addr = cpu_bus_rd(context.pc + 1);
	fetched_data = cpu_bus_rd(effective_addr);
	return NULL;
}
uint8_t ZPX() 
{
	uint8_t effective_addr = 0; //since it's zero-paged, it's only 8 bits
	effective_addr = cpu_bus_rd(context.pc + 1);
	effective_addr += context.x;
	effective_addr &= 0xFF;
	fetched_data = cpu_bus_rd(effective_addr);
	return NULL;
}
uint8_t ZPY()
{
	uint8_t effective_addr = 0; //since it's zero-paged, it's only 8 bits
	effective_addr = cpu_bus_rd(context.pc + 1);
	effective_addr += context.y;
	effective_addr &= 0xFF;
	fetched_data = cpu_bus_rd(effective_addr);
	return NULL;
}

//instructions
uint8_t ADC()
{
	context.a += fetched_data + context.flags_c;	
}
uint8_t AND(); uint8_t ASL(); uint8_t BCC();
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

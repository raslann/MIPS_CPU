#include <stdio.h>
#include <stdint.h>
#include "cpu.h"
#include "utilities.h"
#include "register_names.h"
#include "programming.h"

#define RS_FIELD(instruction) ((instruction & 0x03E00000) >> 21) 
#define RT_FIELD(instruction) ((instruction & 0x001F0000) >> 16)
#define RD_FIELD(instruction) ((instruction & 0x0000F800) >> 11)
#define SHAMT_FIELD(instruction) ((instruction & 0x000007C0) >> 6)  

void add(uint32_t instruction) 
{

  uint8_t rs = RS_FIELD(instruction); 
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  registers[rd] = (uint32_t) ((int32_t) registers[rs] + (int32_t) registers[rt]); 
}

void addu(uint32_t instruction){
	uint8_t rs = RS_FIELD(instruction); 
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  registers[rd] = (uint32_t) ((uint32_t) registers[rs] + (uint32_t) registers[rt]);
}

void sub(uint32_t instruction)
{
	uint8_t rs = RS_FIELD(instruction); 
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  registers[rd] = (uint32_t) ((int32_t) registers[rs] - (int32_t) registers[rt]);

}

void subu(uint32_t instruction)
{
	uint8_t rs = RS_FIELD(instruction); 
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  registers[rd] = (uint32_t) ((uint32_t) registers[rs] - (uint32_t) registers[rt]);

}

void mult(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction); 
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  int64_t result = (int64_t)((int32_t) registers[rs]) * (int64_t)((int32_t) registers[rt]);  
  HI = (uint32_t) (result>>32);
  LO = (uint32_t) (result & 0x00000000FFFFFFFF);  
 
}

void multu(uint32_t instruction) 
{
  uint8_t rs = RS_FIELD(instruction); 
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  uint64_t result = (uint64_t) registers[rs] * (uint64_t) registers[rt]; 
  HI = (uint32_t) (result>>32);
  LO = (uint32_t) (result & 0x00000000FFFFFFFF);  
	
}

  void div(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction); 
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  LO = (uint32_t) ((int32_t) registers[rs] / (int32_t) registers[rt]);
  HI = (uint32_t) ((int32_t) registers[rs] % (int32_t) registers[rt]);
}

  void divu(uint32_t instruction)
  {
  uint8_t rs = RS_FIELD(instruction); 
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  LO = (uint32_t) ((uint32_t) registers[rs] / (uint32_t) registers[rt]);
  HI = (uint32_t) ((uint32_t) registers[rs] % (uint32_t) registers[rt]);
}

void and(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction); 
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  registers[rd] = (uint32_t) ((int32_t) registers[rs] & (int32_t) registers[rt]);
}

void nor(uint32_t instruction)
{
	uint8_t rs = RS_FIELD(instruction); 
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  registers[rd] = ~ ((uint32_t) ((int32_t) registers[rs] | (int32_t) registers[rt]));

}

void or(uint32_t instruction)
{
	uint8_t rs = RS_FIELD(instruction); 
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  registers[rd] = (uint32_t) ((int32_t) registers[rs] | (int32_t) registers[rt]);
}

void xor(uint32_t instruction)
{
	uint8_t rs = RS_FIELD(instruction); 
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  registers[rd] = (uint32_t) ((int32_t) registers[rs] ^ (int32_t) registers[rt]);
}

void sll(uint32_t instruction)
{
	uint8_t rs = RS_FIELD(instruction); 
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  uint8_t shamt = SHAMT_FIELD(instruction); 
  registers[rd] = (uint32_t) ((int32_t) registers[rt] << (int32_t) shamt);
}

void sllv(uint32_t instruction)
{
	uint8_t rs = RS_FIELD(instruction); 
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  registers[rd] = (uint32_t) ((int32_t) registers[rs] << (int32_t) registers[rt]); 
}

void srl(uint32_t instruction)
{
	uint8_t rs = RS_FIELD(instruction); 
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  uint8_t shamt = SHAMT_FIELD(instruction); 
  registers[rd] = (uint32_t) ((int32_t) registers[rt] >> (int32_t) shamt);

}

void sra(uint32_t instruction) 
{
	uint8_t rs = RS_FIELD(instruction); 
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  uint8_t shamt = SHAMT_FIELD(instruction); 
  registers[rd] = (uint32_t) ((int32_t) registers[rt] >> (int32_t) shamt);
}

void srlv(uint32_t instruction)
{
	uint8_t rs = RS_FIELD(instruction); 
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  registers[rd] = (uint32_t) ((int32_t) registers[rs] >> (int32_t) registers[rt]); 
}

void srav(uint32_t instruction)  
{
	uint8_t rs = RS_FIELD(instruction); 
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  registers[rd] = (uint32_t) ((int32_t) registers[rs] >> (int32_t) registers[rt]); 
}

void slt(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction); 
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  if ((int32_t)registers[rs] < (int32_t)registers[rt])
    registers[rd] = 1;
  else
    registers[rd] = 0;
}

void sltu(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction); 
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  if ((uint32_t)registers[rs] < (uint32_t)registers[rt])
    registers[rd] = 1;
  else
    registers[rd] = 0;
}

void jr(uint32_t instruction)
{
	uint8_t rs = RS_FIELD(instruction); 
	npc = (uint32_t)(int32_t) registers[rs];
}

void jalr(uint32_t instruction)
{
	uint8_t rs = RS_FIELD(instruction); 
	registers[31] = pc + 4;
	npc = (uint32_t)(int32_t)registers[rs];
}

void mfhi(uint32_t instruction)
{
  uint8_t rd = RD_FIELD(instruction);
  registers[rd] = HI;
}

void mflo(uint32_t instruction)
{
	uint8_t rd = RD_FIELD(instruction);
  egisters[rd] = LO;

}
        

#include <stdio.h>
#include <stdint.h>
#include "cpu.h"
#include "utilities.h"
#include "register_names.h"
#include "programming.h"

#define RS_FIELD(instruction) ((instruction & 0x03E00000) >> 21) 
#define RT_FIELD(instruction) ((instruction & 0x001F0000) >> 16)
#define I_FIELD(instruction)  (instruction  & 0x0000ffff) 

uint32_t sign_extend(uint16_t imm)
{
	uint32_t result;
	if ((imm & 0x8000) == 0x8000)
    result = (uint32_t) imm | 0xffff0000;
  else
		result = (uint32_t) imm;
	return result;
}

void addi(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint16_t imm = I_FIELD(instruction); 
  registers[rt] = (uint32_t) ((int32_t)registers[rs] + (int32_t) sign_extend(imm)); 
}

void addiu(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint16_t imm = I_FIELD(instruction);
  registers[rt] = (uint32_t) ((uint32_t) registers[rs] + (uint32_t) sign_extend(imm)); 
}

void andi(uint32_t instruction) 
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint16_t imm = I_FIELD(instruction);
  registers[rt] = (uint32_t) ((int32_t) registers[rs] & (int32_t) imm ); 
}

void ori(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint16_t imm = I_FIELD(instruction);
  registers[rt] = (uint32_t) ((int32_t) registers[rs] | (int32_t) imm );
}

void xori(uint32_t instruction)
{
 uint8_t rs = RS_FIELD(instruction);
 uint8_t rt = RT_FIELD(instruction);
 uint16_t imm = I_FIELD(instruction);
 registers[rt] = (uint32_t) ((int32_t) registers[rs] ^ (int32_t) imm );
}

void slti(uint32_t instruction)
{
 uint8_t rs = RS_FIELD(instruction);
 uint8_t rt = RT_FIELD(instruction);
 uint16_t imm = I_FIELD(instruction);
 if ((int32_t)registers[rs] < (int32_t) sign_extend(imm)) 
  registers[rt] = 1;
else
  registers[rt] = 0;
}

void sltiu(uint32_t instruction) 
{
	uint8_t rs = RS_FIELD(instruction);
 uint8_t rt = RT_FIELD(instruction);
 uint16_t imm = I_FIELD(instruction);
 if ((uint32_t)registers[rs] < (uint32_t) sign_extend(imm))
  registers[rt] = 1;
else
  registers[rt] = 0;
}

void beq(uint32_t instruction)
{
 uint8_t rs = RS_FIELD(instruction);
 uint8_t rt = RT_FIELD(instruction);
 uint16_t imm = I_FIELD(instruction);
 if ((int32_t)registers[rs] == (int32_t)registers[rt])
  npc = pc + 4 + ((int32_t) sign_extend(imm) << 2);
}

void bne(uint32_t instruction)
{
 uint8_t rs = RS_FIELD(instruction);
 uint8_t rt = RT_FIELD(instruction);
 uint16_t imm = I_FIELD(instruction);
 if ((int32_t)registers[rs] != (int32_t)registers[rt]) 
  npc = pc + 4 + ((int32_t) sign_extend(imm) << 2);

}
void lb(uint32_t instruction) 
{
 uint8_t rs = RS_FIELD(instruction);
 uint8_t rt = RT_FIELD(instruction);
 uint16_t imm = I_FIELD(instruction);
 uint32_t pointer = (int32_t) registers[rs] + (int32_t) sign_extend(imm);
 uint8_t *pt =(uint8_t *) &memory[pointer];
 registers[rt] = (int32_t) *pt;

}

void lbu(uint32_t instruction) 
{
 uint8_t rs = RS_FIELD(instruction);
 uint8_t rt = RT_FIELD(instruction);
 uint16_t imm = I_FIELD(instruction);
 uint32_t pointer = (int32_t) registers[rs] + (int32_t) sign_extend(imm);
 uint8_t *pt = (uint8_t *) &memory[pointer];
 registers[rt] = (uint32_t) *pt;
}  

void lh(uint32_t instruction)  
{
 uint8_t rs = RS_FIELD(instruction);
 uint8_t rt = RT_FIELD(instruction);
 uint16_t imm = I_FIELD(instruction);
 imm = sign_extend(imm);
 uint32_t pointer = (int32_t) registers[rs] + (int32_t) imm;
 int16_t *pt = (uint16_t *) &memory[pointer];
 registers[rt] = (int32_t) *pt;
}

void lhu(uint32_t instruction) 
{
 uint8_t rs = RS_FIELD(instruction);
 uint8_t rt = RT_FIELD(instruction);
 uint16_t imm = I_FIELD(instruction);
 uint32_t pointer = (int32_t) registers[rs] + (int32_t) sign_extend(imm);
 uint16_t *pt = (uint16_t *) &memory[pointer];
 registers[rt] = (uint32_t) *pt;
}

void lw(uint32_t instruction) 
{
 uint8_t rs = RS_FIELD(instruction);
 uint8_t rt = RT_FIELD(instruction);
 uint16_t imm = I_FIELD(instruction);
 uint32_t pointer = (int32_t) registers[rs] + (int32_t) sign_extend(imm);
 uint32_t *pt = (uint32_t *) &memory[pointer];
 registers[rt] = *pt;
}

void lui(uint32_t instruction)
{
 uint8_t rs = RS_FIELD(instruction);
 uint8_t rt = RT_FIELD(instruction);
 uint16_t imm = I_FIELD(instruction);
 registers[rt] =  (uint32_t) (imm << 16);
}

void sb(uint32_t instruction)  
{
 uint8_t rs = RS_FIELD(instruction);
 uint8_t rt = RT_FIELD(instruction);
 uint16_t imm = I_FIELD(instruction);
 uint8_t mem = (uint8_t)memory[registers[rs]+sign_extend(imm)];
 uint32_t pointer = (int32_t) registers[rs] + (int32_t) sign_extend(imm);
 uint8_t *pt = (uint8_t *) &memory[pointer];
 *pt = (uint8_t) registers[rt];
}

void sh(uint32_t instruction)  
{
 uint8_t rs = RS_FIELD(instruction);
 uint8_t rt = RT_FIELD(instruction);
 uint16_t imm = I_FIELD(instruction);
 uint32_t pointer = (int32_t) registers[rs] + (int32_t) sign_extend(imm);
 uint16_t *pt = (uint16_t *) &memory[pointer];
 *pt = (uint16_t) registers[rt];
}

void sw(uint32_t instruction)   
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint16_t imm = I_FIELD(instruction);
  uint32_t pointer = (int32_t) registers[rs] + (int32_t) sign_extend(imm);
  uint32_t *pt = (uint32_t *) &memory[pointer]; 
  *pt = registers[rt];
}

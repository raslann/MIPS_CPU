#include <stdio.h>
#include <stdint.h>
#include "cpu.h"
#include "register_names.h"
#include "programming.h"

uint32_t ADDRESS_FIELD(uint32_t instruction) {
 	instruction = (instruction & 0b00000011111111111111111111111111);
 	return instruction;
		}

void j(uint32_t instruction) {
	npc = ((pc + 4) & 0xf0000000) | (ADDRESS_FIELD(instruction) << 2);
		}
		
void jal(uint32_t instruction)
{
	
	registers[31] = (pc + 4);
	npc = ((pc + 4) & 0xf0000000) | (ADDRESS_FIELD(instruction) << 2);
}

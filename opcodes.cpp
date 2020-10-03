#include "chip8.h"
#include <iostream>


void chip8::process_op(){

opcode = memory[program_counter] << 8 | memory[program_counter+1];
switch(opcode&0xF000){
	case 0x0000:
		switch(opcode&0x000F){
			case 0x0000:
				for(int i= 0;i<2048,++i){
					graphics[i]= 0x0; }
				
				draw = true;
				program_counter +=2;
				break;
			case 0x000E:
			stack_pointer--;
			program_counter = stack[stack_pointer];
			program_counter += 2;
			break; }
	case 0x1000:
		program_counter = opcode&0x0FFF;
		break;	
	case 0x2000:
		
		stack[stack_pointer]= program_counter;
		stack_pointer++;
		program_counter =opcode & 0x0FFF;
		break;
	case 0x3000:
		if(v_registers[(opcode & 0x0F00)>>8] == (opcode & 0x00FF)){
			program_counter+= 4;}
		else{
			program_counter +=2;
		}
		break;
	case 0x4000:
		if(v_registers[(opcode & 0x0F00)>>8] != (opcode & 0x00FF)){
			program_counter+= 4;}
		else{
			program_counter +=2;
		}
		break;
	case 0x5000:
		if(v_registers[(opcode&0x0F00)>>8] == v_registers[(opcode&0x00F0)>>4]){
			program_counter += 4;
		}
		else{
			program_counter += 2;
		}
		break;
	case 0x6000:
		v_registers[(opcode&0x0F00)>>8] = (opcode&0x00FF)
		program_counter += 2;
		break;
	case 0x7000:
		v_registers[(opcode&0x0F00)>>8] = (opcode&0x00FF)
		program_counter += 2;
		break;
	case 0x8000:
		switch(opcode&0x000F)

	default:
	printf("Unknown opcode: 0x%X", opcode)
}
}




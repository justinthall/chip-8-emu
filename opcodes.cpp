#include "chip8.h"
#include <iostream>
#include <cstdlib>


void chip8::process_op(){
opcode = memory[program_counter] << 8 | memory[program_counter + 1];
std::cout<<std::hex<<opcode<<std::endl;
switch(opcode&0xF000)
{  
	case 0x0000:
		switch(opcode&0x000F){
			case 0x0000: // clears screen
				{
				for(int i= 0;i<2048;++i){
					graphics[i]= 0x0;} 
				draw = true;
				program_counter +=2;
				}
				break;
			case 0x000E: //return
			stack_pointer--;
			program_counter = stack[stack_pointer];
			program_counter += 2;
			break; }
	case 0x1000: // jumps to address
		program_counter = opcode&0x0FFF;
		break;	
	case 0x2000: // calls subroutine
		stack[stack_pointer]= program_counter;
		stack_pointer++;
		program_counter =opcode & 0x0FFF;
		break;
	case 0x3000: // skips instruction if register X = 0x00FF
		if(v_registers[(opcode & 0x0F00)>>8] == (opcode & 0x00FF)){
			program_counter+= 4;}
		else{
			program_counter +=2;
		}
		break;
	case 0x4000: // skips instruction if register X != 0x00FF 
		if(v_registers[(opcode & 0x0F00)>>8] != (opcode & 0x00FF)){
			program_counter+= 4;}
		else{
			program_counter +=2;
		}
		break;
	case 0x5000: //skips instruction if register x != register y
		if(v_registers[(opcode&0x0F00)>>8] == v_registers[(opcode&0x00F0)>>4]){
			program_counter += 4;
		}
		else{
			program_counter += 2;
		}
		break;
	case 0x6000:  //sets register x to 0x00FF
		v_registers[(opcode&0x0F00)>>8] = (opcode&0x00FF);
		program_counter += 2;
		break;
	case 0x7000:  //adds 0x00FF to register x
		v_registers[(opcode&0x0F00)>>8] = (opcode&0x00FF);
		program_counter += 2;
		break;
	case 0x8000:  
		switch(opcode&0x000F){
			case 0x0000:  //sets register x to value of register y
				v_registers[(opcode&0x0F00)>>8] = v_registers[(opcode&0x00F0)>>4];
				program_counter += 2;
				break;
			case 0x0001:  //sets register x to registe  | register y
				v_registers[(opcode&0x0F00)>> 8] = (v_registers[(opcode&0x0F00)>> 8]|v_registers[(opcode&0x00F0)>>4]);
				program_counter += 2;
				break;
			case 0x0002:  // same as above but using &
				v_registers[(opcode&0x0F00)>> 8] = (v_registers[(opcode&0x0F00)>> 8]&v_registers[(opcode&0x00F0)>>4]);
				program_counter += 2;
				break;
			case 0x0003:  //above but xor
				v_registers[(opcode&0x0F00)>> 8] = (v_registers[(opcode&0x0F00)>> 8]^v_registers[(opcode&0x00F0)>>4]);
				program_counter += 2;
				break;
			case 0x0004:  //add value of register y to register x, and sets register f to 0 if theres a carry
				if(v_registers[(opcode & 0x00F0) >> 4] > (0xFF - v_registers[(opcode & 0x0F00) >> 8])){ 
						v_registers[0xF] = 1;}
				else{ 
						v_registers[0xF] = 0;}					
				v_registers[(opcode & 0x0F00) >> 8] += v_registers[(opcode & 0x00F0) >> 4];
				program_counter += 2;
				break;
			case 0x0005:  //subtracts register y from x, sets f to 0 if borrow
				if(v_registers[(opcode&0x00F0)>>4] > v_registers[(opcode&0x0F00)>>8]){
				v_registers[0xF] = 1;
				}
				else{
					v_registers[0xF] = 0;
				}
				v_registers[(opcode & 0x0F00) >> 8] -= v_registers[(opcode & 0x00F0) >> 4];
				program_counter += 2;
				break;
			case 0x0006:  	
				v_registers[0xF] = v_registers[(opcode&0x0F00)>>8] & 0x1;
				v_registers[(opcode&0x0F00)>>8]>>= 1;
				program_counter += 2;
				break;
			case 0x0007:
				if(v_registers[(opcode&0x0F00)>>8] > v_registers[(opcode&0x00F0)>>4]){
				v_registers[0xF] = 0;
				}
				else{
					v_registers[0xF] = 1;
				}
				v_registers[(opcode & 0x00F0) >> 4] -= v_registers[(opcode & 0x0F00) >> 8];
				program_counter += 2;
				break;
			case 0x000E:
			v_registers[0xF] = (v_registers[(opcode&0x0F00)>>8]>>7);
			v_registers[(opcode&0x0F00)>>8] <<= 1;
			program_counter += 2;
			break;
		}
	case 0x9000:
		if(v_registers[(opcode&0x0F00)>>8] != v_registers[(opcode&0x00F0)>>4]){
			program_counter += 4;
		}
		else{
			program_counter += 2;
		}
		break;
	case 0xA000:
		index_register = (opcode&0x0FFF);
		program_counter += 2;
		break;
	case 0xB000:
		program_counter = (opcode&0x0FFF) + v_registers[0];
		break;
	case 0xC000:
		v_registers[(opcode&0x0F00)>>8] = (rand()%255) & (opcode*0x00FF);
		program_counter += 2;
		break;
	case 0xD000:
		{
		short x{v_registers[(opcode&0x0F00)>>8]};
		short y{v_registers[(opcode&0x00F0)>>4]};
		int height{opcode&0x000F};
		unsigned int pixels;
		for (int yaxis{0}; yaxis<height; yaxis++){
			pixels = memory[index_register+yaxis];
			for (int xaxis{0}; xaxis < 8; xaxis++){
				if(((pixels&0x80)>>xaxis) != 0){
					if(graphics[(x+xaxis+((y+yaxis)*64))]== 1){
						v_registers[15] = 1;
					}
					graphics[x + xaxis + ((y + yaxis) * 64)] ^= 1;
				}
			}

		}
		draw = true;
		program_counter += 2;
		}
		break;
	case 0xE000:
		switch(opcode&0x00FF){

			case 0x009E:
				if(key[v_registers[(opcode&0x0F00)>>8]]!= 0){
					program_counter += 4;
				}
				else{
					program_counter += 2;
				}
				break;
			case 0x00A1:
				if(key[v_registers[(opcode&0x0F00)>>8]]== 0){
					program_counter += 4;
				}
				else{
					program_counter += 2;
				}
				break;

		}
		break;
	case 0xF000:
		switch(opcode&0x00FF){
			case 0x0007:
				v_registers[(opcode&0x0F00)>>8] = delay_timer;
				program_counter += 2;
				break;
			case 0x000A:
			{
				bool pressed{false};
				for(int i{0};i<16;i++){
					if(key[i]!=0){
						v_registers[(opcode&0x0F00)>>8] = i;
						pressed = true; }
				}
				if(pressed==false){
					return;}
				program_counter += 2;
			}
			break;
		case 0x0015:
			delay_timer = v_registers[(opcode&0x0F00)>>8];
			program_counter += 2;
			break;
		}
		case 0x0018:
			sound_timer = v_registers[(opcode&0x0F00)>>8];
			program_counter += 2;
			break;
		case 0x001E:
			index_register += v_registers[(opcode&0x0F00)>>8];
			program_counter += 2;
			break;
		case 0x0029:
			index_register = v_registers[(opcode&0x0F00)>>8]* 0x5;
			program_counter += 2;
			break;
		case 0x0033:
			memory[index_register] = v_registers[(opcode & 0x0F00) >> 8] / 100;
			memory[index_register + 1] = (v_registers[(opcode & 0x0F00) >> 8] / 10) % 10;
			memory[index_register + 2] = (v_registers[(opcode & 0x0F00) >> 8] % 100) % 10;					
			program_counter += 2;
			break;
		case 0x0055:
			for(int i; i<v_registers[(opcode&0x0F00)];i++){
				memory[index_register + i] = v_registers[i];
			}
			index_register += ((opcode & 0x0F00) >> 8) + 1;
			program_counter += 2;
			break;
		case 0x0065:
			for(int i; i<v_registers[(opcode&0x0F00)];i++){
				 v_registers[i]=memory[index_register + i];
			}
			program_counter += 2;
			break;
	default:
	printf("Unknown opcode: 0x%X", opcode);
	break;
}
}





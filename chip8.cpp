#include "chip8.h"
#include <algorithm>
#include <fstream>
#include <iostream>

unsigned char fontset[80] = {
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void chip8::init(){
//resets all of our registers and pointers, as well as reseting the current opcode. resets program counter to 0x200 as all programs start there
program_counter = 0x200;
opcode = 0;
index_register = 0;
stack_pointer = 0;
//clear stack, memory, v registers, and graphics to prepare to
std::fill(stack, stack + 16, 0);
std::fill(memory,memory + 4096, 0);
std::fill(v_registers,v_registers + 16, 0);
//std::fill(graphics, graphics + (64*32) , 0);
for(int i{0};i<(64*32); i++)
	graphics[i]= 0;
for(int i = 0; i < 80; i++) {
		 memory[i] = fontset[i];
		 printf("%x %x\n", fontset[i], memory[i]);
		}
}



void chip8::load_game(const char * filename){
	
	std::ifstream handle_game(filename,std::ios::binary);
		handle_game.seekg(0, std::ios::end);
		long size{handle_game.tellg()};
		if (size > 3232) { throw "This game is too big!"; }
		handle_game.clear();
		handle_game.seekg(0, std::ios::beg);
		char* buffer= new char[size]();
		handle_game.read(buffer, size);
		handle_game.close();
	for(int i = 0; i < size; ++i) {
  		memory[i + 512] = buffer[i];
  		}
	delete[] buffer;
}







void chip8::cycle(){

process_op();

}

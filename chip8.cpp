#include "chip8.h"
#include <algorithm>
#include <fstream>
#include <iostream>




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
std::fill(graphics,graphics + (64*32) , 0);
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

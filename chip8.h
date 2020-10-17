#ifndef CHIP8_H
#define CHIP8_H


class chip8
{
private:
unsigned char memory[4096];
unsigned short opcode;
unsigned char v_registers[16];
unsigned short index_register;
unsigned short program_counter;
unsigned short stack[16];
unsigned short stack_pointer;
unsigned char key[16];
public:
void init();
void cycle();
void process_op();
void load_game(const char * filename);
bool draw;
char test[20]{ "This test worked!" };
unsigned int graphics[64 * 32];
unsigned char delay_timer;
unsigned char sound_timer;


};


#endif
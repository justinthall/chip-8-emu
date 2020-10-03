#include <iostream>
#include "chip8.h"
#include <glfw3.h>

int main(int argc, char*argv[]){
chip8 test;
test.init();	
test.load_game(argv[1]);
//glfwInit(); This is to code that needs to be run to start a window

return 0;
}
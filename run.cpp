#include <iostream>
#include "chip8.h"
#include <SDL.h>
#include <iostream>
#include <memory>
#define WINDOW_WIDTH 64
#define HEIGHT 32
#define MODIFER 10

chip8 test;
void update_screen(SDL_Renderer** renderer, SDL_Texture** texture);


int main(int argc, char*argv[]){
  if(argc != 2)
  {
	 std::cout<< "Invalid number of arguments"<<std::endl;
	 return -1;
  }
  test.init();
  test.load_game(argv[1]);
  SDL_Event event;
  //declare window and renderer
  SDL_Renderer *renderer;
  SDL_Window *window;
	// declare double pointers for update screen
  SDL_Renderer **ptr_render;
	SDL_Texture **ptr_texture;   
  if(SDL_Init(SDL_INIT_VIDEO)!=0)
  {
      std::cout << "Error : " << SDL_GetError() << std::endl;
    return -1;
  }
  if(SDL_CreateWindowAndRenderer(HEIGHT * MODIFER, WINDOW_WIDTH* MODIFER, 0, &window, &renderer)!= 0)
  {
    std::cout<<"Error: "<<SDL_GetError()<<std::endl;
    return -1;
  }
	ptr_render = &renderer;
	SDL_Texture* texture{SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, 
    	SDL_TEXTUREACCESS_STREAMING, 
     	WINDOW_WIDTH, WINDOW_WIDTH)};
	ptr_texture = &texture; 	
  while (true) 
  {
   test.process_op();
   if(test.draw==true)
   {
     update_screen(ptr_render,ptr_texture);
   	}
   if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
     break;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}

void update_screen(SDL_Renderer** renderer, SDL_Texture** texture)
{
int pixel[2048];
	int pitch;
if(SDL_LockTexture(*texture, nullptr, reinterpret_cast<void**>(&pixel), &pitch)!=0)
    std::cout << "Error : " << SDL_GetError() << std::endl;
  for (int i = 0; i < 2048; i++)
	{
		if (test.graphics[i]== 0){
			pixel[i] =  0;
		}
		else
		{ 
			pixel[i] = 255;
		}
	}
    SDL_UnlockTexture(*texture);
    SDL_RenderClear(*renderer);
    SDL_RenderCopy(*renderer, *texture, nullptr,nullptr);
    SDL_RenderPresent(*renderer);
    test.draw = false;
}
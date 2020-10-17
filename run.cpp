#include <iostream>
#include "chip8.h"
#include <SDL.h>
#include <iostream>
#include <memory>
#define WINDOW_WIDTH 640
#define HEIGHT 480

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
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
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
	pixel[10] = 1;
  SDL_LockTexture(*texture, NULL, (void**)pixel, &pitch);
  for (int i = 0; i < 2048; i++)
	{
		if (test.graphics[i]== 0){
			pixel[i] = 0000;
		}
		else
		{ 
			pixel[i] = 1;
		}
	}

    SDL_UnlockTexture(*texture);
    SDL_RenderClear(*renderer);
    SDL_RenderCopy(*renderer, *texture, NULL,NULL);
    SDL_RenderPresent(*renderer);
    test.draw = false;
}
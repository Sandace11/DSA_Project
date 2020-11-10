#include <SDL2/SDL.h>
#include "color.h"

SDL_Window* gwin = nullptr;
SDL_Renderer* grender = nullptr;

int main(){
  gwin = SDL_CreateWindow("test win", SDL_WINDOWPOS_UNDEFINED, 
      SDL_WINDOWPOS_UNDEFINED, 480, 600,  
      SDL_WINDOW_RESIZABLE);

  SDL_Event e;

  grender = SDL_CreateRenderer(gwin, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawColor(grender, 0xff, 0xff, 0xff, 0xff);
  SDL_Color test_color = convert_HSL_to_RGB(24, 98, 8);

  bool quit = false;
  while(!quit){
    while(SDL_PollEvent(&e) != 0){
      if (e.type == SDL_QUIT)
        quit = true;
    }
    SDL_SetRenderDrawColor(grender, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(grender);

    SDL_Rect trect = {30, 30, 100, 200};
    SDL_SetRenderDrawColor(grender, test_color.r, test_color.g, test_color.b, test_color.a);
    SDL_RenderFillRect(grender, &trect);
  
    // update screen
    SDL_RenderPresent(grender);
  }

  SDL_DestroyRenderer(grender);
  SDL_DestroyWindow(gwin);
  SDL_Quit();
}

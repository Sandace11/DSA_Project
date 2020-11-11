#include "line.h"
#include <SDL2/SDL.h>

SDL_Window* gwin = nullptr;
SDL_Renderer* grender = nullptr;

int main(){
  gwin = SDL_CreateWindow("test win", SDL_WINDOWPOS_UNDEFINED, 
      SDL_WINDOWPOS_UNDEFINED, 480, 600,  
      SDL_WINDOW_RESIZABLE);

  SDL_Event e;
  SDL_Color stroke = {100, 20, 30, 255};

  Line l1(10, 10, 100, 100);
  Line l2(50, 20, 300, 300);

  l2.set_line_color({0xff, 0x00, 0x00, 0xff});
  // position = 0,1,2 : beginning, middle, end -> default is middle
  l2.set_arrow_by_position(2);

  grender = SDL_CreateRenderer(gwin, -1, SDL_RENDERER_ACCELERATED);

  bool quit = false;
  while(!quit){
    while(SDL_PollEvent(&e) != 0){
      if (e.type == SDL_QUIT)
        quit = true;
    }
    SDL_SetRenderDrawColor(grender, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(grender);
    
    l1.render_line(grender);
    l2.render_line(grender);

    // update screen
    SDL_RenderPresent(grender);
  }

  SDL_DestroyRenderer(grender);
  SDL_DestroyWindow(gwin);
  SDL_Quit();
}

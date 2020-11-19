#include "circle.h"
#include <SDL2/SDL.h>

SDL_Window* gwin = nullptr;
SDL_Renderer* grender = nullptr;

int main(){
  gwin = SDL_CreateWindow("test win", SDL_WINDOWPOS_UNDEFINED, 
      SDL_WINDOWPOS_UNDEFINED, 480, 600,  
      SDL_WINDOW_RESIZABLE);

  SDL_Event e;
  SDL_Color stroke = {100, 20, 30, 255};

  Circle c1(200,200,50);

  Circle c2(300,300,50);

  grender = SDL_CreateRenderer(gwin, -1, SDL_RENDERER_ACCELERATED);

  bool quit = false;
  while(!quit){
    while(SDL_PollEvent(&e) != 0){
      if (e.type == SDL_QUIT)
        quit = true;
    }
    SDL_SetRenderDrawColor(grender, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(grender);

    c1.render_circle_outline(grender);
    c2.render_circle_outline(grender);

    // update screen
    //SDL_RenderPresent(grender);
  }

  SDL_DestroyRenderer(grender);
  SDL_DestroyWindow(gwin);
  SDL_Quit();
}

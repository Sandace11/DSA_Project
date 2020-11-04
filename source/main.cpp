#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include "headers/main.h"

bool init(window *win_props, int height, int width){
  if (SDL_Init(SDL_INIT_VIDEO) < 0){
    printf("SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  win_props->screen_height = height;
  win_props->screen_width = width;
  win_props->window = SDL_CreateWindow("Main Window",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
      win_props->screen_width, win_props->screen_height,
      SDL_WINDOW_RESIZABLE);

  if (win_props->window == nullptr){
    printf("SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  win_props->screen_surface = SDL_GetWindowSurface(win_props->window);
  return true;
}

void close(window* win_props){
  SDL_FreeSurface(win_props->screen_surface);
  win_props->screen_surface = nullptr;

  SDL_DestroyWindow(win_props->window);
  win_props->window = nullptr;

  SDL_Quit();
}

int main(){
  window main_window;
  if (!init(&main_window, 600, 480)){
    printf("Failed to initialize window!");
    return 1;
  }

  bool quit = false;
  SDL_Event event;
  while (!quit){
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT)
        quit = true;
    }
    
    SDL_FillRect(main_window.screen_surface, nullptr, 
        SDL_MapRGB(main_window.screen_surface->format, 0xff, 0xff, 0xff));
    SDL_UpdateWindowSurface(main_window.window);
  }
 
  close(&main_window);  
  return 0;
}

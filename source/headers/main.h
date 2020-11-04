#include <SDL2/SDL.h>

struct window {
  int screen_width = 0;
  int screen_height = 0;
  SDL_Window *window = nullptr;
  SDL_Surface *screen_surface = nullptr;
};



#include <SDL2/SDL.h>

#include "./quick_sort.h"
#include "./huffman_data_structure.cpp"
#include "./huffman.h"

namespace huffman_window {
// window properties
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
} // namespace huffman_window

namespace huffman_data {
  /* Make a priority queue */
  Priority_Queue *g_queue = NULL;
  bool is_idle = false;
}

bool initialize_huffman_window() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Failed to initialize : %s", SDL_GetError());
    return false;
  }

  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    printf("Warning: Linear texture filtering not enabled!");
  }

  huffman_window::window =
      SDL_CreateWindow("Huffman Tree", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, huffman_window::SCREEN_WIDTH,
                       huffman_window::SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

  if (huffman_window::window == nullptr) {
    printf("Failed to create window : %s", SDL_GetError());
    return false;
  }

  huffman_window::renderer =
      SDL_CreateRenderer(huffman_window::window, -1, SDL_RENDERER_ACCELERATED);

  if (huffman_window::renderer == nullptr) {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    return false;
  }

  SDL_SetRenderDrawColor(huffman_window::renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  return true;
}

void close_huffman_window() {
  SDL_DestroyWindow(huffman_window::window);
  huffman_window::window = nullptr;
  SDL_DestroyRenderer(huffman_window::renderer);
  huffman_window::renderer = nullptr;
  SDL_Quit();
}

void get_string_from_user(){
  std::cout << "Enter the string: ";
  std::string user_string;
  std::cin >> user_string;
  huffman_data::g_queue = str_to_priority_queue(user_string);
}

void visualize_huffman_tree() {
  /* Take user's input and yes */
  get_string_from_user();
  if (initialize_huffman_window()) {
    bool quit = false;
    SDL_Event e;

    bool sorted = false;
    while (!quit) {
      while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT || SDL_KEYUP) {
          quit = true;
        }
      }

      /* Do the rest here */

      //->

      /*******************/
    }
    close_window();
  }
}

#include <SDL2/SDL.h>
#include <iostream>
#include <math.h>

#include "../lib/circle.h"
#include "./huffman.h"
#include "./huffman_data_structure.cpp"
#include "./quick_sort.h"

namespace huffman_window {
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
} // namespace huffman_window

namespace huffman_data {
Priority_Queue *g_queue = NULL;
bool is_idle = false;
} // namespace huffman_data

bool initialize_huffman_window() {
  /* This function initializes window */
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Failed to initialize : %s", SDL_GetError());
    return false;
  }

  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    printf("Warning: Linear texture filtering not enabled!");
  }

  huffman_window::window =
      SDL_CreateWindow("SDL_Window", SDL_WINDOWPOS_UNDEFINED,
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
  // TODO: This function also needs to free all the pointers of data structure
  SDL_DestroyWindow(huffman_window::window);
  huffman_window::window = nullptr;
  SDL_DestroyRenderer(huffman_window::renderer);
  huffman_window::renderer = nullptr;
  SDL_Quit();
}

void get_string_from_user() {
  /* This function prompts user for input string */
  std::cout << "Enter the string: ";
  std::string user_string;
  std::cin >> user_string;
  huffman_data::g_queue = str_to_priority_queue(user_string);
}

void print_queue() {
  /* Debugging function foor printing queue */
  for (int i = 0; i < huffman_data::g_queue->queue.size(); ++i) {
    std::cout << huffman_data::g_queue->queue[i]->data << '\n';
  }
}

void clear_screen(){
	SDL_SetRenderDrawColor( huffman_window::renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( huffman_window::renderer );
}

void update_screen(){
  SDL_RenderPresent(huffman_window::renderer);
}

void render_node(Node *node, int depth, int x_coordinate, double bending_angle) {
  // Render node
  Circle this_node = Circle(x_coordinate, 100 + depth * 60, 25);
  this_node.render_circle_outline(huffman_window::renderer);
  if (!node->is_leaf()) {
    //Render right and left child
    // Calculate position for left child and render it
    // child_x = x_coordinate + (60) * (tan(bending_angle/2))
    // child_y = y_coordinate + 60
    render_node(node->left, depth+1, x_coordinate - 60 * tan(bending_angle/2), bending_angle/2);
    // Calculate position for right child and render it
    render_node(node->right, depth+1, x_coordinate + 60 * tan(bending_angle/2), bending_angle/2);
  }
}

void render_priority_queue(Priority_Queue *priority_q) {
  // Function to render on screen, provided queue
  // loop over every node, render using `render_each_node` function
  // center align nodes, with justify like `space around` on CSS

  // Clear the screen
  clear_screen();

  int gap = huffman_window::SCREEN_WIDTH / (priority_q->length() + 1);
  int bending_angle =
      -10 * (priority_q->length()) +
      160; // Bending angle is the angle between lines connecting two children
  for (int i = 0; i < priority_q->length(); ++i) {
    /* Calculate x coordinate of given node */
    // x_coor = gap (i + 1)
    render_node(priority_q->queue[i], 0, gap * (i + 1), bending_angle);
  }

  update_screen();
}

void visualize_huffman_tree() {
  /* Take user's input and yes */
  get_string_from_user();

  // after this step, we have,
  // a priority queue in which nodes are inserted in their priority order

  if (initialize_huffman_window()) {
    bool quit = false;
    SDL_Event e;

    bool processed = false;
    while (!quit) {
      while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT || e.type == SDL_KEYUP) {
          quit = true;
        }
      }

      /* Do the rest here */

      //->
      // while the length of queue is not equal to 1
      // draw
      // wait for few seconds
      // process one branch
      // repeat
      render_priority_queue(huffman_data::g_queue);
      if (huffman_data::g_queue->length() > 1) {
        SDL_Delay(2000);
        combine_once(huffman_data::g_queue);
        std::cout << "Was here\n";
      }

      /*******************/
    }
    close_huffman_window();
  }
}

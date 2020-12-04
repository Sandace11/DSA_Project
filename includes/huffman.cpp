#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "../lib/circle.h"
#include "../lib/line.h"
#include "./huffman.h"
#include "./huffman_data_structure.h"
#include "./huffman_maths.h"

#define RADIUS 20

namespace huffman_window {
const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;
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

  if (huffman_window::window == NULL) {
    printf("Failed to create window : %s", SDL_GetError());
    return false;
  }

  huffman_window::renderer =
      SDL_CreateRenderer(huffman_window::window, -1, SDL_RENDERER_ACCELERATED);

  if (huffman_window::renderer == NULL) {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    return false;
  }

  if (TTF_Init() == -1){
    printf("SDL_ttf could not be initialized!");
    return false;
  }

  SDL_SetRenderDrawColor(huffman_window::renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  return true;
}

void close_huffman_window() {
  // TODO: This function also needs to free all the pointers of data structure
  SDL_DestroyWindow(huffman_window::window);
  huffman_window::window = NULL;
  SDL_DestroyRenderer(huffman_window::renderer);
  huffman_window::renderer = NULL;

  TTF_Quit();
  SDL_Quit();
}

void get_string_from_user() {
  /* This function prompts user for input string */
  std::cout << "Enter the string: ";
  std::string user_string;
  std::getline(std::cin >> std::ws, user_string);
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

double get_y_coords_from_depth(int depth){
  double y_scale_factor = 50 + 15 * huffman_data::g_queue->length();
  return 100 + (depth + 1) * y_scale_factor;
}

void render_node(Node *node, int depth, int x_coordinate, double bending_angle) {
  // Render node
  double y_coordinate = get_y_coords_from_depth(depth);
  Circle this_node = Circle(x_coordinate, y_coordinate, RADIUS, node->frequency, node->data);
  this_node.render_circle_outline(huffman_window::renderer);

  if (!node->is_leaf()) {
    //Render right and left child
    // Calculate position for left child and render it
    // child_x = x_coordinate + (60) * (tan(bending_angle/2))
    // child_y = y_coordinate + 60
    double child_delta_x = 60 * tan(to_rad(bending_angle/2));
    double left_child_x = x_coordinate - child_delta_x;

    double children_y = get_y_coords_from_depth(depth+1);
    double right_child_x = x_coordinate + child_delta_x;

    //Draw lines and node (left)
    Pair left_line_start = parent_line_intersection(x_coordinate, y_coordinate, left_child_x, children_y, RADIUS, "left");
    Pair left_line_end = child_line_intersection(x_coordinate, y_coordinate, left_child_x, children_y, RADIUS, "left");
    Line left_line = Line(left_line_start.x, left_line_start.y, left_line_end.x, left_line_end.y);
    left_line.render_line(huffman_window::renderer);
    render_node(node->left, depth+1, left_child_x, 0.7 * bending_angle);

    // Calculate position for right child and render it
    Pair right_line_start = parent_line_intersection(x_coordinate, y_coordinate, right_child_x, children_y, RADIUS, "right");
    Pair right_line_end = child_line_intersection(x_coordinate, y_coordinate, right_child_x, children_y, RADIUS, "right");
    Line right_line = Line(right_line_start.x, right_line_start.y, right_line_end.x, right_line_end.y);
    right_line.render_line(huffman_window::renderer);
    render_node(node->right, depth+1, right_child_x, 0.7 * bending_angle);
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
      -20 * (priority_q->length()) + 170; // Bending angle is the angle between lines connecting two children
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
        SDL_Delay(3000);
        combine_once(huffman_data::g_queue);
      }

      /*******************/
    }
    close_huffman_window();
  }
}

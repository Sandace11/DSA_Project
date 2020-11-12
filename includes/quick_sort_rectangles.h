#ifndef QUICK_SORT_RECTS_INCLUDED
#define QUICK_SORT_RECTS_INCLUDED

#include <SDL2/SDL.h>

// initializing and closing windows
bool initialize_window_rects();
void close_window_rects();

// all sorting related for color wheel
void render_rects(int pivot_index);
void swap_rects(SDL_Rect arr[], int a, int b);
int partition_rects(SDL_Rect arr[], int start, int end, int pivot_index);
void quick_sort_rects(SDL_Rect arr[], int start, int end);

// function to call to display window and actual sorting visualization
void visualize_quick_sort_rects();

#endif

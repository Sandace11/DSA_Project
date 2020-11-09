#ifndef QUICK_SORT_H_INCLUDED
#define QUICK_SORT_H_INCLUDED

#include <SDL2/SDL.h>

// initializing and closing windows
bool initialize_window();
void close_window();

// all sorting related
void render(int pivot_index);
void swap(SDL_Rect arr[], int a, int b);
int partition(SDL_Rect arr[], int start, int end, int pivot_index);
void quick_sort(SDL_Rect arr[], int start, int end);

// function to call to display window and actual sorting visualization
void visualize_quick_sort();

#endif

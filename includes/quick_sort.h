#ifndef QUICK_SORT_H_INCLUDED
#define QUICK_SORT_H_INCLUDED

#include <SDL2/SDL.h>

// initializing window & array values and closing windows
bool initialize();
void close_window();

// all sorting related
void render(int pivot_index);
void swap(int arr[], int a, int b);
int partition(int arr[], int start, int end, int pivot_index);
void quick_sort(int arr[], int start, int end);

// function to call to display window and actual sorting visualization
void visualize_quick_sort();

#endif

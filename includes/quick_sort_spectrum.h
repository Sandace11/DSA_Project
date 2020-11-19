#ifndef QUICK_SORT_SPECTRUM_INCLUDED
#define QUICK_SORT_SPECTRUM_INCLUDED

#include <SDL2/SDL.h>

// initializing window & array values and closing windows
bool initialize_spectrum();
void init_parameters_spectrum();
void close_window_spectrum();

// all sorting related
void render_spectrum(int pivot_index);
void swap_spectrum(int *a, int *b);
int partition_spectrum(int arr[], int start, int end, int pivot_index);
void quick_sort_spectrum(int arr[], int start, int end);

// function to call to display window and actual sorting visualization
void visualize_quick_sort_spectrum();

#endif

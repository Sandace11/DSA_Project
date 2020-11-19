#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED

#include <SDL2/SDL.h>

// initializing and closing windows
bool initialize_huffman_window();
void close_huffman_window();

// all sorting related
void get_string_from_user();


// function to call to display window and actual sorting visualizati
void clear_screen();
void visualize_huffman_tree();

#endif

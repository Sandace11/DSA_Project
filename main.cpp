#include <iostream>
#include "./includes/quick_sort_rectangles.h"
#include "./includes/quick_sort_spectrum.h"
#include "./includes/huffman.h"

int main(int args, char** argv){
  char ch = '1';
  std::cout <<"Enter a number:\n\
    1) Visualize Quick Sort (Standard Rectangles)\n\
    2) Visualize Quick Sort (Color Spectrum)\n\
    3) Visualize Huffman Tree\n\
    4) Quit\n";
  while(ch){
    std::cin >> ch;
    switch(ch){
      case '1':
        visualize_quick_sort_rects();       
        break;
      case '2':
        visualize_quick_sort_spectrum();      
        break;
      case '3':
        visualize_huffman_tree();
        break;
      case '4':
        std::cout << "Thank you for testing our program!\n";
        return 0;
      default:
        std::cout <<"Program terminated due to invalid input.\n";
        return 0;
        break;
    }
  }
  return 0;
}

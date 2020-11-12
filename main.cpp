#include <iostream>
#include "./includes/quick_sort.h"
#include "./includes/huffman.h"

int main(int args, char** argv){
  char ch;
  std::cout <<"Enter a number:\n\
    1) Visualize Quick Sort\n\
    2) Visualize Huffman Tree\n"; 
  std::cin >> ch;
  switch(ch){
    case '1':
      visualize_quick_sort();
      break;
    case '2':
      visualize_huffman_tree();
      break;
    default:
      std::cout <<"Please make sensible choices!\n";
      break;
  }
  return 0;
}

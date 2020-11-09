#include <iostream>
#include "./includes/quick_sort.h"

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
      std::cout << "Huffman Tree implementation ongoing!\n";
      break;
    default:
      std::cout <<"Please make sensible choices!\n";
      break;
  }
  return 0;
}

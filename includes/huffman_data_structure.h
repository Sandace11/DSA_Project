#include <iostream>
#include <unordered_map>
#include <vector>

class STR_LENGTH_ERROR {};

/* Node for holding data and frequency */
class Node {
public:
  char data;

  unsigned frequency;

  Node *left, *right;

  Node(unsigned frequency, char data = 0) ;

  bool operator>(Node const &nod) ;

  bool is_leaf() ;

};




/* Priority_Queue for huffman tree */
class Priority_Queue {
public:
  std::vector<Node *> queue;

  void insert(Node *new_node);

  Node *remove();

  int length();
};




/* This retard converts a string to Priority_Queue<Nodes> */
Priority_Queue *str_to_priority_queue(std::string &str);




/* This retard combines two nodes with highest priority and inserts
 * the combined node into a single node and pushes to priority queue
 */
void combine_once(Priority_Queue *g_queue);

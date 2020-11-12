#include <iostream>
#include <vector>
#include <unordered_map>

class STR_LENGTH_ERROR{};

/* Node for holding data and frequency */
class Node {
public:
  char data;
  unsigned frequency;
  Node *left, *right;

  Node(unsigned frequency, char data = 0) {
    left = right = NULL;
    this->data = data;
    this->frequency = frequency;
  }

  bool operator>(Node const &nod) { return (this->frequency > nod.frequency); }

  bool is_leaf() { return !(this->left or this->right); }
};

/* Priority_Queue for huffman tree */
class Priority_Queue {
public:
  std::vector<Node *> queue;

  void insert(Node *new_node) {
    /* Traverse until it's position */
    int i=0;
    while (i < queue.size() && *queue[i] > *new_node){
      ++i;
    }

    /* Insert at this position */
    auto iterator = queue.begin() + i;
    queue.insert(iterator, new_node);
  }

  Node* remove() {
    Node *next_item = queue[queue.size() - 1];
    queue.pop_back();
    return next_item;
  }
};

/* This retard converts a string to Priority_Queue<Nodes> */
Priority_Queue* str_to_priority_queue(std::string &str){
  if (str.size() == 0){
    throw STR_LENGTH_ERROR();
  }

  std::unordered_map<char, int> records;
  /* Convert string to hash table */
  for (char x:str){
    if (records.find(x) == records.end()){
      records.insert({x, 1});
    } else {
      auto iter = records.find(x);
      iter->second += 1;
    }
  }

  /* Convert hash table to Nodes and insert to queue */
  Priority_Queue *g_queue = new Priority_Queue();
  for (auto& it:records){
    Node* current = new Node(it.second, it.first);
    g_queue->insert(current);
  }

  return g_queue;
}

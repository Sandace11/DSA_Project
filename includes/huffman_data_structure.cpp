#include <iostream>
#include <unordered_map>
#include <vector>

#include "./huffman_data_structure.h"

/* Node for holding data and frequency */
Node::Node(unsigned frequency, char data) {
  left = right = NULL;
  this->data = data;
  this->frequency = frequency;
}

bool Node::operator>(Node const &nod) {
  return (this->frequency >= nod.frequency);
}

bool Node::is_leaf() { return !(this->left or this->right); }

/* Priority_Queue for huffman tree */

void Priority_Queue::insert(Node *new_node) {
  /* Traverse until it's position */
  int i = 0;
  while (i < queue.size() && *queue[i] > *new_node) {
    ++i;
  }
  /* Insert at this position */
  auto iterator = queue.begin() + i;
  queue.insert(iterator, new_node);
}

Node *Priority_Queue::remove() {
  Node *next_item = queue[queue.size() - 1];
  queue.pop_back();
  return next_item;
}

int Priority_Queue::length() {
  /* Returns length of priority queue (non-recursive) */
  return queue.size();
}

/* This retard converts a string to Priority_Queue<Nodes> */
Priority_Queue *str_to_priority_queue(std::string &str) {
  if (str.size() == 0) {
    throw STR_LENGTH_ERROR();
  }

  std::unordered_map<char, int> records;
  /* Convert string to hash table */
  for (char x : str) {
    if (records.find(x) == records.end()) {
      records.insert({x, 1});
    } else {
      auto iter = records.find(x);
      iter->second += 1;
    }
  }

  /* Convert hash table to Nodes and insert to queue */
  Priority_Queue *g_queue = new Priority_Queue();
  for (auto &it : records) {
    Node *current = new Node(it.second, it.first);
    g_queue->insert(current);
  }

  return g_queue;
}

/* This retard combines two nodes with highest priority and inserts
 * the combined node into a single node and pushes to priority queue
 */
void combine_once(Priority_Queue *g_queue) {
  Node *node_1 = g_queue->remove();
  Node *node_2 = g_queue->remove();

  Node *to_insert = new Node(node_1->frequency + node_2->frequency, '*');
  to_insert->left = node_1;
  to_insert->right = node_2;

  g_queue->insert(to_insert);
}

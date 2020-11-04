int left_child_index(int i) { return i*2+1; }
int right_child_index(int i) { return i*2+2; }
int parent_node_index(int i) { return i-1/2; }

void swap(int *a, int *b){
  int t = *a;
  *a = *b;
  *b = t;
}

void min_heapify(int* array, int size, int index){
  int minimum = index;
  int left_child = left_child_index(index);
  int right_child = right_child_index(index);

  if (left_child_index(index) < size && array[left_child] < array[minimum])
    minimum = left_child_index(index); 

  if (right_child_index(index) < size && array[right_child] < array[minimum])
    minimum = right_child_index(index);

  if (minimum != index){
    swap(&array[index], &array[minimum]);
    min_heapify(array, size, minimum);
  }
}


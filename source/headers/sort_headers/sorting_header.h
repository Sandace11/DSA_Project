// Header file to generate set of array for sorting

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

void print_array(int* array, int size){
    for (int i = 0; i < size; i++)
       printf("%d ", array[i]); 
    printf("\n");
}

int* array_reverse_sorted_integers(int size){
    int* array = (int *)malloc(size * sizeof(int)); 
    for (int i = 0; i < size; i++)
        array[i] = size - i; 
    return array;
}

int* array_random_integers(int size, int min, int max){
    srand(time(0));
    int* array = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        array[i] = rand() % (max - min + 1) + min;
    return array;  
}

double sort_and_measure_time(int* array, int size, void (*fp)(int*, int)){ 
    clock_t start = clock();
    (*fp)(array, size);
    clock_t stop = clock();

    return (double)(stop - start) / CLOCKS_PER_SEC;
}

void cleanup_array(int* array){
    free(array);
}

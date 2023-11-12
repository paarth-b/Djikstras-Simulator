#ifndef HEAP_H
#define HEAP_H 1
#include <fstream>
#include "data_structures.h"

HEAP *init(int capacity);
void print(HEAP *heap);
void write(HEAP *heap, FILE *fp);
void read(HEAP *heap, FILE *fp, int flag);
void insert(HEAP *heap, double *key);
void extractMin(HEAP *heap, int flag);
void decreaseKey(HEAP *heap, double *position, double *key);

#endif
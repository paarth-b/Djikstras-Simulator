#ifndef HEAP_H
#define HEAP_H 1
#include <fstream>
#include "stack.h"

HEAP *init(int capacity);
void print(HEAP *heap);
void write(HEAP *heap, FILE *fp);
void read(HEAP *heap, FILE *fp, int flag);
void insert(HEAP *heap, VERTEX *V);
VERTEX *extractMin(HEAP *heap);
void decreaseKey(HEAP *heap, VERTEX *v, double *key);

#endif
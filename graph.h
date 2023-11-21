#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include "data_structures.h"
#include "heap.h"

void buildGraph(FILE *fp, int vertices, int edges, int flag, bool isDirected);

void printGraph(int edges, int vertices);

#endif // GRAPH_H

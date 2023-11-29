#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include "heap.h"

void buildGraph(FILE *fp, int vertices, int edges, int flag, bool isDirected);

void printGraph();

void singlePair(int source, int destination);

void singleSource(int source);

void printLength(int source, int destination);

void printPath(int source, int destination);

#endif // GRAPH_H

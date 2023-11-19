#include "graph.h"
#include <stdlib.h>
#include <cstdio>
#include <iostream>

using namespace std;

VERTEX *V;
deque<EDGE> *adj;

void formConnection(EDGE *edge, int flag, bool isDirected)
{
    if (isDirected)
    {
        if (flag == 1)
        {
            adj[edge->start_edge].push_front(*edge);
        }
        else
        {
            adj[edge->start_edge].push_back(*edge);
        }
    }
    else
    {
        if (flag == 1)
        {
            adj[edge->start_edge].push_front(*edge);
            adj[edge->end_edge].push_front(*edge);
        }
        else
        {
            adj[edge->start_edge].push_back(*edge);
            adj[edge->end_edge].push_back(*edge);
        }
    }
}

void buildGraph(FILE *fp, int vertices, int edges, int flag, bool isDirected)
{
    int enter = 0;
    int index, start_vertex, end_vertex;
    double weight;

    V = new VERTEX[vertices];
    adj = new deque<EDGE>[vertices];

    while (enter < edges) // each iteration of an edge written in file
    {
        fscanf(fp, "%d %d %d", &index, &start_vertex, &end_vertex);
        fscanf(fp, "%lf", &weight);

        EDGE *edge = new EDGE();
        edge->index = index;
        edge->start_edge = start_vertex;
        edge->end_edge = end_vertex;
        edge->weight = weight;

        formConnection(edge, flag, isDirected);
        V[edge->start_edge].neighbor = adj[edge->start_edge];

        delete edge;
        enter++;
    }
}

#include "graph.h"
#include <stdlib.h>
#include <cstdio>
#include <iostream>

using namespace std;

VERTEX *V;

void formConnection(EDGE *edge, int flag, bool isDirected)
{
    if (isDirected)
    {
        if (flag == 1)
        {
            V[edge->start_edge].adj.push_front(*edge);
        }
        else
        {
            V[edge->start_edge].adj.push_back(*edge);
        }
    }
    else
    {
        if (flag == 1)
        {
            V[edge->start_edge].adj.push_front(*edge);
            V[edge->end_edge].adj.push_front(*edge);
        }
        else
        {
            V[edge->start_edge].adj.push_back(*edge);
            V[edge->end_edge].adj.push_back(*edge);
        }
    }
}

void buildGraph(FILE *fp, int vertices, int edges, int flag, bool isDirected)
{
    int enter = 0;
    int index, start_vertex, end_vertex;
    double weight;

    V = new VERTEX[vertices];
    printf("Final V color: %c\n", V[vertices - 1].color);
    printf("V color: %c\n", V[0].color);

    while (enter < edges) // each iteration of an edge written in file
    {
        fscanf(fp, "%d %d %d %lf", &index, &start_vertex, &end_vertex, &weight);

        EDGE *edge = new EDGE();
        edge->index = index;
        edge->start_edge = start_vertex - 1;
        edge->end_edge = end_vertex - 1;
        edge->weight = weight;

        formConnection(edge, flag, isDirected);

        delete edge;
        enter++;
    }
}

void printGraph(int edges, int vertices)
{
    for (int node = 0; node < vertices; node++)
    {
        printf("ADJ[%d]:-->", node + 1);
        for (int edge = 0; edge < V[node].adj.size(); edge++)
        {
            printf("[%d %d: %.2lf]", V[node].adj[edge].start_edge + 1, V[node].adj[edge].end_edge + 1, V[node].adj[edge].weight);
            if (edge != V[node].adj.size() - 1)
                printf("-->");
            else
                printf("\n");
        }
    }
}
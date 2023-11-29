#include "graph.h"
#include <stdlib.h>
#include <cstdio>
#include <iostream>

using namespace std;

VERTEX *V;
int vertices, edges;

void flipVertices(EDGE *edge)
{
    int temp;
    temp = edge->start_edge;
    edge->start_edge = edge->end_edge;
    edge->end_edge = temp;
}

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
            flipVertices(edge);
            V[edge->start_edge].adj.push_front(*edge);
        }
        else
        {
            V[edge->start_edge].adj.push_back(*edge);
            flipVertices(edge);
            V[edge->start_edge].adj.push_back(*edge);
        }
    }
}

void buildGraph(FILE *fp, int numV, int numEdges, int flag, bool isDirected)
{
    edges = numEdges;
    vertices = numV;
    int enter = 0;
    int index, start_vertex, end_vertex;
    double weight;

    V = new VERTEX[vertices];
    for (int i = 0; i < vertices; i++)
        V[i].name = i + 1;

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

void printGraph()
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

void relax(VERTEX *u, VERTEX *v, double weight)
{
    if (v->dist > u->dist + weight)
    {
        printf("U dist: %lf\n", u->dist);
        v->dist = u->dist + weight;
        v->pi = u->name;
    }
}

void singlePair(int source, int destination)
{
    V[source - 1].dist = 0;
    // initialize set
    HEAP *queue = init(vertices);
    for (int i = 0; i < vertices; i++)
    {
        insert(queue, &V[i]);
        V[i].heapPos = i;
    }
    print(queue);
    while (queue->size != 0)
    {
        VERTEX *u = extractMin(queue);
        printf("V: %d, Distance: %.2lf, Pi: %.2d, HeapPos: %lf\n", u->name, u->dist, u->pi, u->heapPos);
        if (u->name == destination)
            break;
        for (int i = 0; i < u->adj.size(); i++)
        {
            VERTEX *v = &V[u->adj[i].end_edge];
            printf("Name: %d\n", v->name);
            double curr_dist = v->dist;
            printf("Old V Dist: %lf\n", curr_dist);
            relax(u, v, u->adj[i].weight);
            printf("Relaxed: %d to %d, weight %.2lf\n", u->name, v->name, u->adj[i].weight);
            printf("New V Dist: %lf\n", v->dist);
            if (curr_dist > v->dist)
                decreaseKey(queue, v, &v->dist);
        }
        for (int i = 0; i < vertices; i++)
            printf("Vertex: %d, Distance: %.2lf, Pi: %.2d\n", V[i].name, V[i].dist, V[i].pi);
    }
}

void singleSource(int source)
{
    V[source].dist = 0;
    // initialize set
    HEAP *queue = init(vertices);
    for (int i = 0; i < vertices; i++)
    {
        insert(queue, &V[i]);
        V[i].heapPos = i;
    }
    while (queue->size != 0)
    {
        VERTEX *u = extractMin(queue);
        for (int i = 0; i < u->adj.size(); i++)
        {
            VERTEX *v = &V[u->adj[i].end_edge];
            double curr_dist = v->dist;

            relax(u, v, u->adj[i].weight);
            if (curr_dist > v->dist)
                decreaseKey(queue, v, &v->dist);
        }
    }
}

void printPath(int source, int destination)
{
    STACK *stack = new STACK();
    if (destination == source)
        push(*stack, &V[source]);
    else if (V[destination].pi == -1)
        printf("There is no path from %d to %d", source + 1, destination + 1);
    else
    {
        int prevNode = V[destination].pi;
        push(*stack, &V[destination]);
        printPath(source, prevNode);
    }
    while (!isEmpty(*stack))
    {
        VERTEX *v = pop(*stack);
        printf("[%d:    %.2lf]", v->name, v->dist);
        if (!isEmpty(*stack))
            printf("-->");
        else
            printf(".");
    }
}
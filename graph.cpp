#include "graph.h"
#include <stdlib.h>
#include <cstdio>
#include <iostream>

using namespace std;

VERTEX *V;
int pathBuilt[2] = {-2, -2};
int vertices, edges;

void flipVertices(EDGE *edge)
{
    int temp;
    temp = edge->start_edge;
    edge->start_edge = edge->end_edge;
    edge->end_edge = temp;
}

// Helper method to form connections between vertices when building graph
void formConnection(EDGE *edge, int flag, bool isDirected)
{
    if (isDirected) // check if graph is directed
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

    V = new VERTEX[vertices]; // initialize vertices
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

        enter++;
    }
}

void printGraph()
{
    for (int node = 0; node < vertices; node++) // for each vertex in array
    {
        printf("ADJ[%d]:-->", node + 1);
        if (V[node].adj.size() == 0)
            printf("\n");

        for (int edge = 0; edge < V[node].adj.size(); edge++) // for each connecting edge
        {
            printf("[%d %d: %.2lf]",
                   V[node].adj[edge].start_edge + 1,
                   V[node].adj[edge].end_edge + 1,
                   V[node].adj[edge].weight);

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
        v->dist = u->dist + weight;
        v->pi = u->name;
    }
}

void djikstra(int source, int destination)
{
    for (int i = 0; i < vertices; i++)
    {
        V[i].dist = DBL_MAX;
        V[i].pi = -1;
    }

    HEAP *queue = init(vertices);

    for (int i = 0; i < vertices; i++)
    {
        insert(queue, &V[i]);
        V[i].heapPos = i;
    }

    decreaseKey(queue, source - 1, 0);

    while (queue->size != 0)
    {
        VERTEX *u = extractMin(queue);

        if (u->name == destination)
        {
            pathBuilt[0] = source;
            pathBuilt[1] = destination;
            break;
        }

        for (int i = 0; i < u->adj.size(); i++)
        {
            VERTEX *v = &V[u->adj[i].end_edge];

            double curr_dist = v->dist;

            relax(u, v, u->adj[i].weight);

            if (curr_dist > v->dist)
                decreaseKey(queue, v->heapPos, v->dist);
        }
    }

    pathBuilt[0] = source;
    pathBuilt[1] = destination;
    delete queue;
}

bool buildStack(int source, int destination, STACK *stack)
{
    if (destination == source)
        push(stack, &V[source]);

    else if (V[destination].pi < 0)
        return true;

    else
    {
        int prevNode = V[destination].pi - 1;
        push(stack, &V[destination]);
        if (buildStack(source, prevNode, stack))
            return true;
    }
    return false;
}

bool checkEnds(int source, int destination)
{
    bool destExists = true;
    if (destination != pathBuilt[1] && pathBuilt[1] != -1)
        destExists = false;

    if (pathBuilt[0] != source || destExists == false)
        return false;
    else
        return true;
}

void printPath(int source, int destination)
{
    if (checkEnds(source, destination) == false)
        return;

    STACK *stack = new STACK();
    if (buildStack(source - 1, destination - 1, stack) == true)
    {
        printf("There is no path from %d to %d.\n", source, destination);
        return;
    }

    printf("The shortest path from %d to %d is:\n", source, destination);
    while (!isEmpty(stack))
    {
        VERTEX *v = pop(stack);

        printf("[%d:%8.2lf]", v->name, v->dist);
        if (!isEmpty(stack))
            printf("-->");
        else
            printf(".\n");
    }
}

void printLength(int source, int destination)
{
    if (checkEnds(source, destination) == false)
        return;

    STACK *stack = new STACK();
    if (buildStack(source - 1, destination - 1, stack) == true)
    {
        printf("There is no path from %d to %d.\n", source, destination);
        return;
    }
    printf("The length of the shortest path from %d to %d is:     %.2lf\n",
           source, destination, V[destination - 1].dist);
}
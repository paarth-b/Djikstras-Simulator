#include "graph.h"
#include <stdlib.h>
#include <cstdio>
#include <iostream>

using namespace std;

VERTEX *V;
int pathBuilt = -1;
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
        if (V[node].adj.size() == 0)
        {
            printf("\n");
            continue;
        }
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
    // printf("Heap cap: %d\n", queue->capacity);

    insert(queue, &V[source - 1]);
    for (int i = 0; i < vertices; i++)
    {
        if (i != source - 1)
            insert(queue, &V[i]);
    }
    // V[source - 1].dist = 0;
    queue->H[0]->dist = 0;

    // for (int i = 0; i < vertices; i++)
    //     printf("Vertex: %d, Distance: %.2lf, Pi: %.2d\n", V[i].name, V[i].dist, V[i].pi);

    while (queue->size != 0)
    {
        VERTEX *u = extractMin(queue);
        if (u->name == destination)
            break;
        // printf("V: %d, Distance: %.2lf, Pi: %.2d\n", u->name, u->dist, u->pi);
        for (int i = 0; i < u->adj.size(); i++)
        {
            VERTEX *v = &V[u->adj[i].end_edge];
            // printf("Name: %d\n", v->name);
            double curr_dist = v->dist;
            // printf("Old V Dist: %lf\n", curr_dist);
            relax(u, v, u->adj[i].weight);
            // printf("Relaxed: %d to %d, weight %.2lf\n", u->name, v->name, u->adj[i].weight);
            // printf("New V Dist: %lf\n", v->dist);
            if (curr_dist > v->dist)
                decreaseKey(queue, v, &v->dist);
        }
    }
    // for (int i = 0; i < vertices; i++)
    //     printf("Vertex: %d, Distance: %.2lf, Pi: %.2d\n", V[i].name, V[i].dist, V[i].pi);
    pathBuilt = source;
    delete queue;
}

void singlePair(int source, int destination)
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
    }
    queue->H[0]->dist = 0;
    // print(queue);
    while (queue->size != 0)
    {
        VERTEX *u = extractMin(queue);
        // printf("V: %d, Distance: %.2lf, Pi: %.2d\n", u->name, u->dist, u->pi);
        if (u->name == destination)
            break;
        for (int i = 0; i < u->adj.size(); i++)
        {
            VERTEX *v = &V[u->adj[i].end_edge];
            // printf("Name: %d\n", v->name);
            double curr_dist = v->dist;
            // printf("Old V Dist: %lf\n", curr_dist);
            relax(u, v, u->adj[i].weight);
            // printf("Relaxed: %d to %d, weight %.2lf\n", u->name, v->name, u->adj[i].weight);
            // printf("New V Dist: %lf\n", v->dist);
            if (curr_dist > v->dist)
                decreaseKey(queue, v, &v->dist);
        }
        // for (int i = 0; i < vertices; i++)
        //     printf("Vertex: %d, Pi: %.2d\n", V[i].name, V[i].pi);
    }
    pathBuilt = source;
    delete queue;
}

void singleSource(int source)
{
    djikstra(source, -1);
}

bool buildStack(int source, int destination, STACK *stack)
{
    // printf("Source: %d, Destination: %d\n", source, destination);
    if (destination == source)
    {
        push(stack, &V[source]);
    }
    else if (V[destination].pi < 0)
    {
        // printf("Node: %d, Pi: %d\n", V[destination].name, V[destination].pi);
        return true;
    }
    else
    {
        int prevNode = V[destination].pi - 1;
        // printf("PrevNode: %d\n", prevNode);
        push(stack, &V[destination]);
        if (buildStack(source, prevNode, stack))
            return true;
    }
    return false;
}
void printPath(int source, int destination)
{
    if (pathBuilt != source)
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
        printf("[%d:    %.2lf]", v->name, v->dist);
        if (!isEmpty(stack))
            printf("-->");
        else
            printf(".\n");
    }
}

void printLength(int source, int destination)
{
    if (pathBuilt != source)
        return;
    STACK *stack = new STACK();
    if (buildStack(source - 1, destination - 1, stack) == true)
    {
        printf("There is no path from %d to %d.\n", source, destination);
        return;
    }
    printf("The length of the shortest path from %d to %d is:     %.2lf\n", source, destination, V[destination - 1].dist);
}
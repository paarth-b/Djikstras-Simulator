#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "util.h"
#include "graph.h"

int main(int argc, char **argv)
{
    FILE *fp;
    int source, destination;
    int returnV, vertices, edges;
    int flag = 1;
    bool isDirected = false;
    char Word[100];

    if (argc < 4 || atoi(argv[3]) > 2)
    {
        fprintf(stderr, "Usage: %s <InputFile> <GraphType> <Flag>\n", argv[0]);
        exit(0);
    }

    if (atoi(argv[3]) == 2) // check flag
        flag = 2;
    fp = fopen(argv[1], "r"); // Open input file in read mode
    fscanf(fp, "%d", &vertices);
    fscanf(fp, "%d", &edges);

    if (strcmp(argv[2], "DirectedGraph") == 0)
    {
        isDirected = true;
    }

    buildGraph(fp, vertices, edges, flag, isDirected);

    fclose(fp); // close file after reading graph

    while (1)
    {
        returnV = nextInstruction(Word, &source, &destination);
        if (returnV == 0)
        {
            fprintf(stderr, "Warning: Invalid instruction\n");
            continue;
        }

        if (strcmp(Word, "Stop") == 0)
        {
            return 0;
        }

        if (strcmp(Word, "PrintADJ") == 0)
        {
            printGraph();
            continue;
        }
        if (strcmp(Word, "SinglePair") == 0)
        {
            djikstra(source, destination);
            continue;
        }
        if (strcmp(Word, "SingleSource") == 0)
        {
            djikstra(source, -1);
            continue;
        }
        if (strcmp(Word, "PrintLength") == 0)
        {
            printLength(source, destination);
            continue;
        }
        if (strcmp(Word, "PrintPath") == 0)
        {
            printPath(source, destination);
            continue;
        }
    }

    return 1;
}

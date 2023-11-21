#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "util.h"
#include "graph.h"

int main(int argc, char **argv)
{
    FILE *fp;
    HEAP *heap;
    double key, position;
    int returnV, vertices, edges;
    int flag = 1;
    bool isDirected;
    char Word[100];

    if (argc < 4)
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
    else if (strcmp(argv[2], "UndirectedGraph") == 0)
    {
        isDirected = false;
    }

    buildGraph(fp, vertices, edges, flag, isDirected);
    fclose(fp); // close file after reading graph

    while (1)
    {
        returnV = nextInstruction(Word, &key, &position);

        // printf("Instruction: %s\n", Word);

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
            printGraph(edges, vertices);
            continue;
        }
    }

    return 1;
}

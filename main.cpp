#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "util.h"
#include "heap.h"

int main(int argc, char **argv)
{
    FILE *fp;
    HEAP *heap;
    double key, position;
    int returnV, vertices, edges;
    int flag = 1;
    char Word[100];

    if (argc < 4)
    {
        fprintf(stderr, "Usage: %s <ifile> <ofile> flag\n", argv[0]);
        exit(0);
    }

    if (atoi(argv[3]) == 2) // check flag
        flag = 2;

    fscanf(stdin, "%d", vertices);
    fscanf(stdin, "%d", edges);

    V = (VERTEX **)malloc((vertices + 1) * sizeof(VERTEX *));
    ADJ = (EDGE **)malloc((vertices + 1) * sizeof(EDGE *));

    for (int i = 1; i <= vertices; i++)
    {
        V[i] = (VERTEX *)malloc(sizeof(VERTEX));
        V[i]->vertexNumber = i;
        V[i]->edgeList = NULL;
        ADJ[i] = NULL;
    }

    for (int i = 1; i <= edges; i++)
    {
        int edgeIndex, startVertex, endVertex;
        double weight;
        fscanf(fp, "%d %d %d %lf", &edgeIndex, &startVertex, &endVertex, &weight);

        EDGE *newEdge = (EDGE *)malloc(sizeof(EDGE));
        newEdge->edgeIndex = edgeIndex;
        newEdge->startVertex = startVertex;
        newEdge->endVertex = endVertex;
        newEdge->weight = weight;
        newEdge->next = NULL;

        if (flag == 1)
        {
            if (ADJ[startVertex] == NULL)
            {
                ADJ[startVertex] = newEdge;
            }
            else
            {
                newEdge->next = ADJ[startVertex];
                ADJ[startVertex] = newEdge;
            }

            if (startVertex != endVertex)
            {
                EDGE *newEdge2 = (EDGE *)malloc(sizeof(EDGE));
                newEdge2->edgeIndex = edgeIndex;
                newEdge2->startVertex = endVertex;
                newEdge2->endVertex = startVertex;
                newEdge2->weight = weight;
                newEdge2->next = NULL;

                if (ADJ[endVertex] == NULL)
                {
                    ADJ[endVertex] = newEdge2;
                }
                else
                {
                    newEdge2->next = ADJ[endVertex];
                    ADJ[endVertex] = newEdge2;
                }
            }
        }
        else if (flag == 2)
        {
            if (ADJ[startVertex] == NULL)
            {
                ADJ[startVertex] = newEdge;
            }
            else
            {
                EDGE *temp = ADJ[startVertex];
                while (temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = newEdge;
            }

            if (startVertex != endVertex)
            {
                EDGE *newEdge2 = (EDGE *)malloc(sizeof(EDGE));
                newEdge2->edgeIndex = edgeIndex;
                newEdge2->startVertex = endVertex;
                newEdge2->endVertex = startVertex;
                newEdge2->weight = weight;
                newEdge2->next = NULL;

                if (ADJ[endVertex] == NULL)
                {
                    ADJ[endVertex] = newEdge2;
                }
                else
                {
                    EDGE *temp = ADJ[endVertex];
                    while (temp->next != NULL)
                    {
                        temp = temp->next;
                    }
                    temp->next = newEdge2;
                }
            }
        }
    }

    fclose(fp);
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

        if (strcmp(Word, "Init") == 0)
        {
            heap = init(key);
        }

        if (strcmp(Word, "Print") == 0)
        {
            if (heap == NULL)
            {
                std::cerr << "Error: Heap is NULL";
                continue;
            }
            print(heap);
        }

        if (strcmp(Word, "Write") == 0)
        {
            if (heap == NULL)
            { // If heap is null, print error message and return
                std::cerr << "Error: Heap is NULL";
                continue;
            }
            fp = fopen(argv[2], "w");
            if (!fp)
            { // If fp is null, print error message and continue
                std::cerr << "Error: File could not be opened" << std::endl;
                continue;
            }
            write(heap, fp);
            fclose(fp);
        }

        if (strcmp(Word, "Read") == 0)
        {
            if (heap == NULL)
            { // If heap is null, print error message and return
                std::cerr << "Error: Heap is NULL";
                continue;
            }
            fp = fopen(argv[1], "r");
            if (!fp)
            { // If fp is null, print error message and continue
                std::cerr << "Error: File could not be opened" << std::endl;
                continue;
            }

            read(heap, fp, flag);
            fclose(fp);
        }

        if (strcmp(Word, "Insert") == 0 || strcmp(Word, "ert") == 0)
        {
            if (heap == NULL)
            { // If heap is null, print error message and return
                std::cerr << "Error: Heap is NULL";
                continue;
            }
            fscanf(stdin, "%lf", &key);
            insert(heap, &key);
        }

        if (strcmp(Word, "ExtractMin") == 0)
        {
            if (heap == NULL)
            { // If heap is null, print error message and return
                std::cerr << "Error: Heap is NULL";
                continue;
            }
            extractMin(heap, flag);
        }

        if (strcmp(Word, "DecreaseKey") == 0)
        {
            if (heap == NULL)
            { // If heap is null, print error message and return
                std::cerr << "Error: Heap is NULL";
                continue;
            }

            decreaseKey(heap, &position, &key);
        }
    }

    return 1;
}

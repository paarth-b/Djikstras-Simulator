#include <stdio.h>
#include <string.h>
#include "util.h"

int nextInstruction(char *Word, int *source, int *destination)
{
    int returnV;
    fscanf(stdin, "%s", Word);

    if (strcmp(Word, "Stop") == 0)
        return 1;
    if (strcmp(Word, "PrintADJ") == 0)
        return 1;

    if (strcmp(Word, "SinglePair") == 0)
    {
        returnV = fscanf(stdin, "%d %d", source, destination);
        if (returnV == 2)
            return 1;
        else
            return 0;
    }
    if (strcmp(Word, "SingleSource") == 0)
    {
        returnV = fscanf(stdin, "%d", source);
        if (returnV == 1)
            return 1;
        else
            return 0;
    }
    if (strcmp(Word, "PrintLength") == 0)
    {
        returnV = fscanf(stdin, "%d %d", source, destination);
        if (returnV == 2)
            return 1;
        else
            return 0;
    }
    if (strcmp(Word, "PrintPath") == 0)
    {
        returnV = fscanf(stdin, "%d %d", source, destination);
        if (returnV == 2)
            return 1;
        else
            return 0;
    }

    return 0;
}

#include <stdio.h>
#include <string.h>
#include "util.h"

int nextInstruction(char *Word, double *key, double *position)
{
    int returnV;
    fscanf(stdin, "%s", Word);

    if (strcmp(Word, "Stop") == 0)
        return 1;
    if (strcmp(Word, "Print") == 0)
        return 1;
    if (strcmp(Word, "Write") == 0)
        return 1;
    if (strcmp(Word, "Read") == 0)
        return 1;
    if (strcmp(Word, "ExtractMin") == 0)
        return 1;

    if (strcmp(Word, "Init") == 0)
    {
        returnV = fscanf(stdin, "%lf", key);

        if (returnV == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    if (strcmp(Word, "Insert") == 0 || strcmp(Word, "ert") == 0)
    {
        returnV = fscanf(stdin, "%lf", key);
        if (returnV == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    if (strcmp(Word, "DecreaseKey") == 0)
    {
        returnV = fscanf(stdin, "%lf%lf", position, key);
        if (returnV == 2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    return 0;
}

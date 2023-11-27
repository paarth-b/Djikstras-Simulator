#include <stdio.h>
#include <string.h>
#include "util.h"

int nextInstruction(char *Word, double *key, double *position)
{
    int returnV;
    fscanf(stdin, "%s", Word);

    if (strcmp(Word, "Stop") == 0)
        return 1;
    if (strcmp(Word, "PrintADJ") == 0)
        return 1;
    if (strcmp(Word, "Write") == 0)
        return 1;
    if (strcmp(Word, "Read") == 0)
        return 1;
    if (strcmp(Word, "ExtractMin") == 0)
        return 1;
    return 0;
}

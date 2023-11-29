#ifndef STACK_H
#define STACK_H
#include "data_structures.h"

void push(STACK stack, VERTEX *v);

VERTEX *pop(STACK stack);

VERTEX *peek(STACK stack);

bool isEmpty(STACK stack);

#endif // STACK_H

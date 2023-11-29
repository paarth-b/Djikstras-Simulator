#include "stack.h"

void push(STACK stack, VERTEX *v)
{
    stack.S[stack.top++] = v;
}

VERTEX *pop(STACK stack)
{
    return stack.S[stack.top--];
}

VERTEX *peek(STACK stack)
{
    return stack.S[stack.top];
}

bool isEmpty(STACK stack)
{
    return stack.top == 0;
}
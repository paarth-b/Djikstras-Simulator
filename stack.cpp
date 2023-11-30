#include "stack.h"

void push(STACK *stack, VERTEX *v)
{
    stack->S[stack->top] = v;
    stack->top++;
}

VERTEX *pop(STACK *stack)
{
    stack->top--;
    return stack->S[stack->top];
}

VERTEX *peek(STACK *stack)
{
    return stack->S[stack->top - 1];
}

bool isEmpty(STACK *stack)
{
    if (stack->top == 0)
        return true;
    else
        return false;
}
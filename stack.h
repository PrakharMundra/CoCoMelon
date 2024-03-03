#ifndef STACK_H
#define STACK_H

#include "parserDef.h"
#include "symbolTable.h"
#define stacksize 1000;

typedef struct stack
{
    gSym *arr;
    int topOfStack;
    int size;
} stack;

stack* s;

stack* create_stack();
void push(stack* s, gSym ele);
gSym top(stack* s);
void pop(stack* s);
void enlargeStack(stack* s);
bool isEmpty(stack *s);

#endif
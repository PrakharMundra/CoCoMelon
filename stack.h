#include <stdio.h>

#include "parserDef.h"

#define stacksize 2;

typedef struct stack
{
    gSym *arr;
    int top;
    int size;
} stack;

stack* s;

stack* create_stack();
void push(stack* s, gSym ele);
bool isEmpty(stack *s);

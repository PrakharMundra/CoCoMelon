/* Group Number- 25
ID-2021A7PS0576P Name-Nek Manchanda
ID-2021A7PS2429P Name-Utkarsh Sharma
ID-2021A7PS2683P Name-Yash Sejpal
ID-2021A7PS2689P Name-Nishant Singh
ID-2021A7PS2694P Name-Prakhar Mundra */
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
#include "stack.h"
#include <stdio.h>

stack *create_stack()
{
    s = (stack *)malloc(sizeof(stack));
    s->size = stacksize;
    s->arr = (gSym *)malloc(sizeof(gSym) * s->size); 
    s->topOfStack = 0;
    gSym temp;
    temp.isTerminal = true;
    temp.t = TK_DOLLAR;
    s->arr[s->topOfStack] = temp;
    s->topOfStack++;
    temp.isTerminal = false;
    temp.nt = program;
    s->arr[s->topOfStack] = temp;
    // s->top++;
    return s;
}

void enlargeStack(stack *s)
{
    int newSize = 2 * s->size;
    gSym *newArr = (gSym *)realloc(s->arr, sizeof(gSym) * newSize);
    // s->arr = newArr;
    s->size = newSize;
}
void push(stack *s, gSym ele)
{
    if (s->topOfStack == s->size-1)
    {
        printf("push() : stack full already\n");
        enlargeStack(s);
        printf(" push() : stack enlarged\n");
    }
    s->topOfStack++;
    s->arr[s->topOfStack] = ele;
    return;
}
bool isEmpty(stack *s)
{
    if (s->topOfStack == 0)
        return true;
    return false;
}

void pop(stack *s)
{
    gSym ele;
    if (isEmpty(s))
    {
        printf("pop() : Stack is already empty \n");
        return;
    }
    else
    {
        ele = s->arr[s->topOfStack - 1];
        s->topOfStack--;
        return;
    }
}
gSym top(stack *s)
{
    if (isEmpty(s))
    {
        printf("top() : Stack is empty \n");
        return;
    }
    gSym ele = s->arr[s->topOfStack];
    // if (ele.isTerminal == true)
    //     printf("top of stack is : %s\n", Terminals[ele.t]);
    // else
    //     printf("top of stack is : %s\n", nonTerminals[ele.nt]);

    return ele;
}

#include "stack.h"
#include <stdio.h>

stack *create_stack()
{
    s = (stack *)malloc(sizeof(stack));
    s->size = stacksize;
    s->arr = (gSym *)malloc(sizeof(gSym) * s->size);
    s->top = 0;
    gSym topOfStack;
    topOfStack.isTerminal = false;
    topOfStack.nt = program;
    s->arr[s->top] = topOfStack;
    s->top++;
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
    if (s->top == s->size)
    {
        printf("stack full already\n");
        enlargeStack(s);
        printf("  stack enlarged\n");
    }
    s->arr[s->top] = ele;
    s->top++;
    return;
}
bool isEmpty(stack *s)
{
    if (s->top == 0)
        return true;
    return false;
}

void pop(stack *s)
{
    gSym ele;
    if (isEmpty(s))
    {
        printf("Stack is already empty \n");
        return;
    }
    else
    {
        ele = s->arr[s->top - 1];
        s->top--;
        return;
    }
}
gSym top(stack *s)
{
    if (isEmpty(s))
    {
        printf("Stack is empty \n");
        return;
    }
    gSym ele = s->arr[s->top - 1];
    if (ele.isTerminal == true)
        printf("top of stack is : %s\n", Terminals[ele.t]);
    else
        printf("top of stack is : %s\n", nonTerminals[ele.nt]);

    return ele;
}

int main()
{   
    stack *s = create_stack(); // 1 element added by default
    gSym ele = top(s);
    printf("---\n");

    gSym ele1;
    ele1.isTerminal = true;
    ele1.t = 5;

    printf("%d,%d\n"s->top,s->size);
    push(s, ele1); // 2 elements now
    ele = top(s);

    printf("---\n");
    gSym ele2;
    ele2.isTerminal = false;
    ele2.nt = 2;

    push(s, ele2); // 3 elements now
    ele = top(s);
    printf("---\n");
    pop(s); // 2 elements now
    ele = top(s);
    pop(s); // 1 element now
    ele = top(s);
    pop(s); // no element now
    ele = top(s);
    printf("---\n");
    push(s, ele1); // 1 element now
    ele = top(s);
    printf("---\n");
    return 0;
}
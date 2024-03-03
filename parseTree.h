
#include "parserDef.h"

typedef struct parseTree{
    struct parseTree * parentNode;
    struct parseTree * leftmost;
    struct parseTree * rightmost;
    struct parseTree * nextNode;
    gSym nodeValue;
}parseTree;

parseTree * createTree();
parseTree * createNode(gSym nodeValue);
void addChild(parseTree * parent,parseTree * childNode);
void inorderTraversal(parseTree * startNode);

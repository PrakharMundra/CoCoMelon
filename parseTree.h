#ifndef parseTre
#define parseTre
#include "parserDef.h"
#include "symbolTable.h"

typedef struct parseTree{
    struct parseTree * parentNode;
    struct parseTree * leftmost;
    struct parseTree * rightmost;
    struct parseTree * nextNode;
    gSym nodeValue;
}parseTree;

parseTree * root;

parseTree * createTree();
parseTree * createNode(gSym nodeValue);
void addChild(parseTree * parent,parseTree * childNode);
void inorderTraversal(parseTree * startNode);
#endif
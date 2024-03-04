/* Group Number- 25
ID-2021A7PS0576P Name-Nek Manchanda
ID-2021A7PS2429P Name-Utkarsh Sharma
ID-2021A7PS2683P Name-Yash Sejpal
ID-2021A7PS2689P Name-Nishant Singh
ID-2021A7PS2694P Name-Prakhar Mundra */
#ifndef parseTre
#define parseTre
#include "parserDef.h"
#include "symbolTable.h"
#include "lexerDef.h"

typedef struct parseTree{
    struct parseTree * parentNode;
    struct parseTree * leftmost;
    struct parseTree * rightmost;
    struct parseTree * nextNode;
    gSym nodeValue;
    tkn token;
}parseTree;

parseTree * root;
FILE* poi;
parseTree * createTree();
parseTree * createNode(gSym nodeValue);
void addChild(parseTree * parent,parseTree * childNode);
void inorderTraversal(parseTree * startNode);
#endif
#include<stdio.h>
#include "parseTree.h"

parseTree * createTree();
parseTree * createNode(gSym nodeValue);
void addChild(parseTree * parent,parseTree * childNode);
void inorderTraversal(parseTree * startNode);


parseTree * createTree()
{
    parseTree * startNode=(parseTree *)malloc(sizeof(parseTree));
    startNode->parentNode=NULL;
    startNode->leftmost=NULL;
    startNode->rightmost=NULL;
    startNode->nextNode=NULL;
    gSym nodeVal;
    nodeVal.isTerminal=false;
    nodeVal.nt=program;
    startNode->nodeValue=nodeVal;

    return startNode;
}

parseTree * createNode(gSym nodeValue)
{
    parseTree * addNode=(parseTree *)malloc(sizeof(parseTree));
    addNode->parentNode=NULL;
    addNode->nodeValue=nodeValue;
    addNode->leftmost=NULL;
    addNode->rightmost=NULL;
    addNode->nextNode=NULL;
    return addNode;
}

void addChild(parseTree * parent, parseTree * childNode)
{
    childNode->parent=parent;
    parent->rightmost->nextNode=childNode;

    if(parent->leftmost==NULL)
    parent->leftmost=childNode;

    parent->rightmost=childNode;
}

void inorderTraversal(parseTree * startNode)
{
    if(startNode==NULL)
    return ;

    while(startNode->nextNode->nextNode==NULL)

}




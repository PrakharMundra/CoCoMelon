#include<stdio.h>
#include "parseTree.h"

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
    childNode->parentNode=parent;
    childNode->nextNode=parent->leftmost;
    parent->leftmost=childNode;

    if(parent->rightmost==NULL)
    parent->rightmost=childNode;

}

void print(parseTree * startNode)
{
    if(startNode==NULL)
    return ;

    while(startNode->leftmost!=NULL)
    {
        if(startNode->nodeValue.isTerminal==true)
        printf("%s \n",Terminals[startNode->nodeValue.t]);
        else
        printf("%s \n",nonTerminals[startNode->nodeValue.nt]);
        startNode=startNode->leftmost;
    }
    
}

void inorderTraversal(parseTree * startNode)
{
    if(startNode==NULL)
    return ;

    parseTree * leftNode=startNode->leftmost;
    while(leftNode!=NULL && leftNode->nextNode!=NULL)
    {
        inorderTraversal(leftNode);
        leftNode=leftNode->nextNode;
    }

    if(startNode->nodeValue.isTerminal)
    {
        printf("%s ",Terminals[startNode->nodeValue.t]);
        printf("\n");
    }
    else
    {
        printf("%s ",nonTerminals[startNode->nodeValue.nt]);
        printf("\n");
    }

    if(leftNode!=NULL)
    {
        inorderTraversal(leftNode);
    }
}


int main()
{
    parseTree * mainTree=createTree();
    gSym g1;
    g1.isTerminal=true;
    g1.t=TK_MUL;

    parseTree * node1=createNode(g1);
    addChild(mainTree,node1);
    g1.t=TK_DIV;
    parseTree * node7=createNode(g1);
    addChild(mainTree,node7);
    g1.isTerminal=true;
    g1.t=TK_COMMA;
    parseTree * node2=createNode(g1);
    addChild(node1,node2);
    g1.t=TK_COLON;
    parseTree * node3=createNode(g1);
    addChild(node2,node3);
    g1.t=TK_DEFINETYPE;
    parseTree * node6=createNode(g1);
    addChild(node2,node6);
    g1.t=TK_REAL;
    parseTree * node4=createNode(g1);
    addChild(node3,node4);
    g1.t=TK_CL;
    parseTree * node5=createNode(g1);
    addChild(node4,node5);


    //print(mainTree);
    inorderTraversal(mainTree);
}

  




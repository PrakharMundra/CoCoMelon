/* Group Number- 25
ID-2021A7PS0576P Name-Nek Manchanda
ID-2021A7PS2429P Name-Utkarsh Sharma
ID-2021A7PS2683P Name-Yash Sejpal
ID-2021A7PS2689P Name-Nishant Singh
ID-2021A7PS2694P Name-Prakhar Mundra */
#include "parseTree.h"

parseTree *createTree()
{

    parseTree *startNode = (parseTree *)malloc(sizeof(parseTree));
    startNode->parentNode = NULL;
    startNode->leftmost = NULL;
    startNode->rightmost = NULL;
    startNode->nextNode = NULL;
    gSym nodeVal;
    nodeVal.isTerminal = false;
    nodeVal.nt = program;
    startNode->nodeValue = nodeVal;

    return startNode;
}

parseTree *createNode(gSym nodeValue)
{
    parseTree *addNode = (parseTree *)malloc(sizeof(parseTree));
    addNode->parentNode = NULL;
    addNode->nodeValue = nodeValue;
    addNode->leftmost = NULL;
    addNode->rightmost = NULL;
    addNode->nextNode = NULL;
    return addNode;
}

void addChild(parseTree *parent, parseTree *childNode)
{
    childNode->parentNode = parent;
    childNode->nextNode = parent->leftmost;
    parent->leftmost = childNode;
    if (parent->rightmost == NULL)
        parent->rightmost = childNode;
}

// void inorderTraversal(parseTree * startNode)
// {
//     if(startNode==NULL)
//     return ;

//     // parseTree * leftNode=startNode->leftmost;
//     // while(leftNode!=NULL && leftNode->nextNode!=NULL)
//     // {
//     //     inorderTraversal(leftNode);
//     //     leftNode=leftNode->nextNode;
//     // }

//     // if(startNode->nodeValue.isTerminal)
//     // {
//     //     printf("%s->",Terminals[startNode->nodeValue.t]);
//     // }
//     // else
//     // {
//     //     printf("%s-> ",nonTerminals[startNode->nodeValue.nt]);
//     // }

//     // if(leftNode!=NULL)
//     // {
//     //     inorderTraversal(leftNode);
//     // }

//     //program
//     //tk_div                 tk_mul
//     //tk_cl tk_real tk_definetype          tk_colon tk_comma
//     //output tk_cl tk_div tk_real tk_definetype program tk_colon tk_mul tk_comma

//     parseTree * leftNode=startNode->leftmost;
//     inorderTraversal(leftNode);

//     if(startNode->nodeValue.isTerminal)
//     {
//         printf("%s->",Terminals[startNode->nodeValue.t]);
//     }
//     else
//     {
//         printf("%s-> ",nonTerminals[startNode->nodeValue.nt]);
//     }

//     if(leftNode!=NULL)
//     {
//         leftNode=leftNode->nextNode;
//         while(leftNode!=NULL)
//         {
//             inorderTraversal(leftNode);
//             leftNode=leftNode->nextNode;
//         }
//     }

// }
void inorderTraversal(parseTree *startNode)
{

    if (startNode == NULL)
        return;
    // Traversing the leftmost node.
    parseTree *leftNode = startNode->leftmost;
    inorderTraversal(leftNode);

    // Printing the value of start Node.
    if (startNode->nodeValue.isTerminal)
    {
        if (strcmp(startNode->token.name, "TK_NUM") == 0)
        {
            // printf("%s->",Terminals[startNode->nodeValue.t]);
            // fprintf(poi,"%s->",Terminals[startNode->nodeValue.t]);
            if (startNode->parentNode != NULL)
            {
                printf("1a\n");
                fprintf(poi, "lexeme- %-20d Line No- %-20d tokenName- %-20s parentNodeSymbol- %-20s isLeafNode- Yes nodeSymbol- %-20s \n", startNode->token.num, startNode->token.line, startNode->token.name, nonTerminals[startNode->parentNode->nodeValue.nt], Terminals[startNode->nodeValue.t]);
                printf("1b\n");
            }
            else
            {
                printf("2a\n");
                fprintf(poi, "lexeme- %-20d Line No- %-20d tokenName- %-20s parentNodeSymbol- %-20s isLeafNode- Yes nodeSymbol- %-20s \n", startNode->token.num, startNode->token.line, startNode->token.name, "NULL", Terminals[startNode->nodeValue.t]);
                printf("2b\n");
            }
        }
        else if (strcmp(startNode->token.name, "TK_RNUM") == 0)
        {
            if (startNode->parentNode != NULL)
            {
                printf("3a\n");
                fprintf(poi, "lexeme- %-20f Line No- %-20d tokenName- %-20s parentNodeSymbol- %-20s isLeafNode- Yes nodeSymbol- %-20s \n", startNode->token.rnum, startNode->token.line, startNode->token.name, nonTerminals[startNode->parentNode->nodeValue.nt], Terminals[startNode->nodeValue.t]);
                printf("3b\n");
            }
            else
            {
                printf("4a\n");
                fprintf(poi, "lexeme- %-20f Line No- %-20d tokenName- %-20s parentNodeSymbol- %-20s isLeafNode- Yes nodeSymbol- %-20s \n", startNode->token.rnum, startNode->token.line, startNode->token.name, "NULL", Terminals[startNode->nodeValue.t]);
                printf("4b\n");
            }
        }
        else
        {
            if (strcmp(startNode->token.name, "TK_EPS") == 0)
            {
                printf("5a\n");
                fprintf(poi, "lexeme- %-20s Line No-%-20d tokenName- %-20s  parentNodeSymbol- %-20s isLeafNode- No nodeSymbol- %-20s \n", "----", startNode->token.line, startNode->token.name, nonTerminals[startNode->parentNode->nodeValue.nt], Terminals[startNode->nodeValue.t]);
                printf("5b\n");
            }
            else if (startNode->parentNode != NULL)
            {
                printf("6a\n");
                fprintf(poi, "lexeme- %-20s Line No- %-20d tokenName- %-20s parentNodeSymbol- %-20s isLeafNode- Yes nodeSymbol- %-20s \n", startNode->token.lexeme_value, startNode->token.line, startNode->token.name, nonTerminals[startNode->parentNode->nodeValue.nt], Terminals[startNode->nodeValue.t]);
                printf("6b\n");
            }
            else
            {
                printf("7a\n");
                fprintf(poi, "lexeme- %-20s Line No- %-20d tokenName- %-20s parentNodeSymbol- %-20s isLeafNode- Yes nodeSymbol- %-20s \n", startNode->token.lexeme_value, startNode->token.line, startNode->token.name, "NULL", Terminals[startNode->nodeValue.t]);
                printf("7b\n");
            }
        }
    }
    else
    {
        // printf("%s-> ",nonTerminals[startNode->nodeValue.nt]);
        //  fprintf(poi,"%s->",nonTerminals[startNode->nodeValue.nt]);
        if (startNode->parentNode != NULL)
        {
            printf("8a\n");
            fprintf(poi, "lexeme- %-20s Line No- %-20s  tokenName- %-20s  parentNodeSymbol- %-20s isLeafNode- No nodeSymbol- %-20s \n", "----", "----", "NULL", nonTerminals[startNode->parentNode->nodeValue.nt], nonTerminals[startNode->nodeValue.nt]);
            printf("8b\n");
        }
        else
        {
            printf("9a\n");
            fprintf(poi, "lexeme- %-20s Line No- %-20s  tokenName- %-20s  parentNodeSymbol- NULL isLeafNode- No nodeSymbol- %-20s \n", "----", "----", "NULL", nonTerminals[startNode->nodeValue.nt]);
            printf("9b\n");
        }
    }
    // Recursively travelling the rest of the child Nodes except the leftmost One, if present.
    if (leftNode != NULL)
    {
        leftNode = leftNode->nextNode;
        while (leftNode != NULL)
        {
            inorderTraversal(leftNode);
            leftNode = leftNode->nextNode;
        }
    }
}

// int main()
// {

//     //program
//     //tk_mul                     tk_div
//     //tk_comma tk_colon            tk
//     //output tk_comma tk_mul tk_colon program tk_definetype tk_real tk_div tk_cl
//     parseTree * mainTree=createTree();
//     gSym g1;
//     g1.isTerminal=true;
//     g1.t=TK_MUL;

//     parseTree * node1=createNode(g1);
//     addChild(mainTree,node1);

//     g1.t=TK_DIV;
//     parseTree * node2=createNode(g1);
//     addChild(mainTree,node2);
//     g1.isTerminal=true;
//     g1.t=TK_COMMA;
//     parseTree * node3=createNode(g1);
//     addChild(node1,node3);
//     g1.t=TK_COLON;
//     parseTree * node4=createNode(g1);
//     addChild(node1,node4);
//     g1.t=TK_DEFINETYPE;
//     parseTree * node5=createNode(g1);
//     addChild(node2,node5);
//     g1.t=TK_REAL;
//     parseTree * node6=createNode(g1);
//     addChild(node2,node6);
//     g1.t=TK_CL;
//     parseTree * node7=createNode(g1);
//     addChild(node2,node7);

//     //print(mainTree);
//     inorderTraversal(mainTree);
// }

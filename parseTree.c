/* -----------------------------------------
             Group Number- 25
ID-2021A7PS0576P Name-Nek Manchanda
ID-2021A7PS2429P Name-Utkarsh Sharma
ID-2021A7PS2683P Name-Yash Sejpal
ID-2021A7PS2689P Name-Nishant Singh
ID-2021A7PS2694P Name-Prakhar Mundra
--------------------------------------------- */

#include "parseTree.h"
extern parseTree *root;
extern FILE *poi;
parseTree *createTree() {
  /*Allocating the space for the starting node. As the rootNode is always
  program the node value is initialised with non-terminal program*/
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

parseTree *createNode(gSym nodeValue) {
  // Allocating the space for the node and initialising its node Value to
  // nodeValue
  parseTree *addNode = (parseTree *)malloc(sizeof(parseTree));
  addNode->parentNode = NULL;
  addNode->nodeValue = nodeValue;
  addNode->leftmost = NULL;
  addNode->rightmost = NULL;
  addNode->nextNode = NULL;
  return addNode;
}

void addChild(parseTree *parent, parseTree *childNode) {
  // Adding the child node from right to left
  childNode->parentNode = parent;
  childNode->nextNode = parent->leftmost;
  parent->leftmost = childNode;
  // In the first case where there is only node it is both leftmost and
  // rightmost
  if (parent->rightmost == NULL)
    parent->rightmost = childNode;
}

void inorderTraversal(parseTree *startNode) {
  if (startNode == NULL)
    return;
  // Traversing the leftmost node.
  parseTree *leftNode = startNode->leftmost;
  inorderTraversal(leftNode);

  // Printing the value of start Node.
  if (startNode->nodeValue.isTerminal == true) {
    if (strcmp(startNode->token.name, "TK_NUM") == 0) {
      if (startNode->parentNode != NULL) {
        fprintf(
            poi,
            "%-30d %-30d %-30s "
            "%-30s %-30s %-30s \n",
            startNode->token.num, startNode->token.line, startNode->token.name,
            nonTerminals[startNode->parentNode->nodeValue.nt], "Yes",
            Terminals[startNode->nodeValue.t]);
      } else {
        fprintf(
            poi,
            "%-30d %-30d %-30s  "
            "%-30s %-30s %-30s \n",
            startNode->token.num, startNode->token.line, startNode->token.name,
            "NULL", "Yes", Terminals[startNode->nodeValue.t]);
      }
    } else if (strcmp(startNode->token.name, "TK_RNUM") == 0) {
      if (startNode->parentNode != NULL) {
        fprintf(
            poi,
            "%-30f %-30d %-30s "
            "%-30s %-30s %-30s \n",
            startNode->token.rnum, startNode->token.line, startNode->token.name,
            nonTerminals[startNode->parentNode->nodeValue.nt], "Yes",
            Terminals[startNode->nodeValue.t]);
      } else {
        fprintf(
            poi,
            "%-30f %-30d %-30s "
            "%-30s %-30s %-30s \n",
            startNode->token.rnum, startNode->token.line, startNode->token.name,
            "NULL", "Yes", Terminals[startNode->nodeValue.t]);
      }
    } else {
      if (strcmp(startNode->token.name, "TK_EPS") == 0) {
        fprintf(
            poi,
            "%-30s %-30d %-30s "
            "%-30s %-30s %-30s \n",
            "----", startNode->token.line, startNode->token.name,
            nonTerminals[startNode->parentNode->nodeValue.nt], "No",
            Terminals[startNode->nodeValue.t]);
      } else if (startNode->parentNode != NULL) {
        fprintf(
            poi,
            "%-30s %-30d %-30s "
            "%-30s %-30s %-30s \n",
            startNode->token.lexeme_value, startNode->token.line,
            startNode->token.name,
            nonTerminals[startNode->parentNode->nodeValue.nt], "Yes",
            Terminals[startNode->nodeValue.t]);
      } else {
        fprintf(
            poi,
            "%-30s %-30d %-30s "
            "%-30s %-30s %-30s \n",
            startNode->token.lexeme_value, startNode->token.line,
            startNode->token.name, "NULL", "Yes",
            Terminals[startNode->nodeValue.t]);
      }
    }
  } else {
    if (startNode->parentNode != NULL) {
      fprintf(poi,
              "%-30s %-30s %-30s "
              "%-30s %-30s %-30s \n",
              "----", "----", "NULL",
              nonTerminals[startNode->parentNode->nodeValue.nt], "No",
              nonTerminals[startNode->nodeValue.nt]);
    } else {
      fprintf(poi,
              " %-30s %-30s %-30s "
              "%-30s %-30s %-30s \n",
              "----", "----", "NULL", "NULL", "No",
              nonTerminals[startNode->nodeValue.nt]);
    }
  }
  // Recursively travelling the rest of the child Nodes except the leftmost One,
  // if present.
  if (leftNode != NULL) {
    leftNode = leftNode->nextNode;
    while (leftNode != NULL) {
      inorderTraversal(leftNode);
      leftNode = leftNode->nextNode;
    }
  }
}

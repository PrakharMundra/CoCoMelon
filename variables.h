/* -----------------------------------------
             Group Number- 25
ID-2021A7PS0576P Name-Nek Manchanda
ID-2021A7PS2429P Name-Utkarsh Sharma
ID-2021A7PS2683P Name-Yash Sejpal
ID-2021A7PS2689P Name-Nishant Singh
ID-2021A7PS2694P Name-Prakhar Mundra
--------------------------------------------- */

#include "lexer.h"
#include "parserDef.h"
#include "parseTree.h"
#include "stack.h"

extern Rule Grammar[MAX_SIZE];
extern Set firstSet[NT_SIZE];
extern Set followSet[NT_SIZE];
extern int visitedFirst[NT_SIZE];
extern int visitedFollow[NT_SIZE];
extern Rule ParseTable[NT_SIZE][T_SIZE - 1];

extern char buffer[BUFFER_SIZE];
extern Table *symbol_table;
extern int lexemeBegin;
extern int retraction;
extern int forward;
extern int line_no;
extern int state;

extern parseTree *root;
extern FILE *poi;
extern stack *s;
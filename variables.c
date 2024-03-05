/* -----------------------------------------
             Group Number- 25
ID-2021A7PS0576P Name-Nek Manchanda
ID-2021A7PS2429P Name-Utkarsh Sharma
ID-2021A7PS2683P Name-Yash Sejpal
ID-2021A7PS2689P Name-Nishant Singh
ID-2021A7PS2694P Name-Prakhar Mundra
--------------------------------------------- */

#include "variables.h"
Rule Grammar[MAX_SIZE];
Set firstSet[NT_SIZE];
Set followSet[NT_SIZE];
int visitedFirst[NT_SIZE];
int visitedFollow[NT_SIZE];
Rule ParseTable[NT_SIZE][T_SIZE - 1];
char buffer[BUFFER_SIZE];
Table *symbol_table;
int lexemeBegin;
int retraction;
int forward;
int line_no;
int state;
parseTree *root;
FILE *poi;
stack *s;
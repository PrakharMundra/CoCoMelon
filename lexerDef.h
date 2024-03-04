/* Group Number- 25
ID-2021A7PS0576P Name-Nek Manchanda
ID-2021A7PS2429P Name-Utkarsh Sharma
ID-2021A7PS2683P Name-Yash Sejpal
ID-2021A7PS2689P Name-Nishant Singh
ID-2021A7PS2694P Name-Prakhar Mundra */
#ifndef lexerDef
#define lexerDef
#define BUFFER_SIZE 4096
#define maxlen 65
#include <stdio.h>
#include "symbolTable.h"

 typedef struct tokeninfo {
   char* name;
    union{
  
    char* lexeme_value;
    int num;
    double rnum;
    };

    int line;
 } tkn;

char buffer[BUFFER_SIZE];
Table* symbol_table;
int lexemeBegin;
int retraction;
int forward;
int line_no;
int state;
#endif




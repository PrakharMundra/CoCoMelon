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




/* -----------------------------------------
             Group Number- 25
ID-2021A7PS0576P Name-Nek Manchanda
ID-2021A7PS2429P Name-Utkarsh Sharma
ID-2021A7PS2683P Name-Yash Sejpal
ID-2021A7PS2689P Name-Nishant Singh
ID-2021A7PS2694P Name-Prakhar Mundra
--------------------------------------------- */

#ifndef lexerDef
#define lexerDef
#define BUFFER_SIZE 4096
#define maxlen 65
#include "symbolTable.h"
#include <stdio.h>

typedef struct tokeninfo {
  char *name;
  union {

    char *lexeme_value;
    int num;
    double rnum;
  };

  int line;
} tkn;

#endif

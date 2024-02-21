#include "lexerDef.h"
#include <stdio.h>

void retract(int num);
char getChar(FILE* fp);
void lexer_init();
char* get_name();
int get_len();
struct tokeninfo getNextToken(FILE* fp);



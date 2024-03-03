#ifndef lexer
#define lexer
#include "lexerDef.h"
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void retract(int num);
char getChar(FILE* fp);
void lexer_init();
char* get_name();
int get_len();
struct tokeninfo getNextToken(FILE* fp);
long long hashFunc(char* inp);
Table* createTable();
Entry* createEntry(char* value,char* token);
char* search(Table* table,char* value);
void insert(Table* table,char* value,char* token);
void populate_lookup_table();
removeComments(char *testcaseFile, char *cleanFile);

#endif

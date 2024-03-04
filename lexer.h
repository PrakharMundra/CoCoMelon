/* Group Number- 25
ID-2021A7PS0576P Name-Nek Manchanda
ID-2021A7PS2429P Name-Utkarsh Sharma
ID-2021A7PS2683P Name-Yash Sejpal
ID-2021A7PS2689P Name-Nishant Singh
ID-2021A7PS2694P Name-Prakhar Mundra */
#ifndef lexer
#define lexer
#include "lexerDef.h"
#include "symbolTable.h"
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
tkn getNextToken(FILE* fp);
// long long hashFunc(char* inp);
// Table* createTable();
// Entry* createEntry(char* value,char* token);
// char* search(Table* table,char* value);
// void insert(Table* table,char* value,char* token);
void printTokens(char * testfile);
void populate_lookup_table();
void removeComments(char *testcaseFile, char *cleanFile);
#endif

/* -----------------------------------------
             Group Number- 25
ID-2021A7PS0576P Name-Nek Manchanda
ID-2021A7PS2429P Name-Utkarsh Sharma
ID-2021A7PS2683P Name-Yash Sejpal
ID-2021A7PS2689P Name-Nishant Singh
ID-2021A7PS2694P Name-Prakhar Mundra
--------------------------------------------- */

#ifndef symbolTable
#define symbolTable
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define tableSize 100003
typedef struct Entry{
    char* value;
    char* token;
}Entry;
typedef struct Table{
    Entry* entries[tableSize];
}Table;
char* search(Table* table,char* value);

extern char *Terminals[];
extern char *nonTerminals[];


long long hashFunc(char *inp);
Table *createTable();
Entry *createEntry(char * value, char* token);
char* search(Table* table, char* value);
void insert(Table* table, char* value, char* token);


#endif

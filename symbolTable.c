#include "lexer.h"
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
long long hashFunc(char* inp)
{
    //we use the rolling polynomial hash method with formula s[i]*p^i mod m
    int prime=53; //prime number close to number of alphabets(upper and lowercase)
    long long power=1;
    int modulo=1e5+3;//large prime number (probability of collision is 1/modulo)
    long long res=0;//final key value to be returned
    for(int i=0;i<strlen(inp);i++)
    {
        res=(((inp[i]-'0'+1)*power)+res)%modulo;
        // printf("inp[i] : %c, res : %d\n",inp[i],res);
        power=(power*prime)%modulo;
    }
    return res;
}
//this function is to create the table and initialize all the entries to null
Table* createTable()
{
    //printf("qq");
    int sz=tableSize*sizeof(Entry*);
    Table* symTable = malloc(sz);
    // Entry* en;
    // en->token = "";
    // en->value = 1;
    //printf("qq");
    for(int i=0;i<tableSize;i++)
    {
        
        // printf("qq1");
        symTable->entries[i]=NULL;

    }
    // printf("qq\n");
    return symTable;
}
// this function is to create an entry of the symbol table
Entry* createEntry(char* value,char* token)
{
    // printf("you");
    Entry* entry=(Entry*)malloc(sizeof(Entry));
    entry->value =(char*)malloc(strlen(value) +1);
    entry->token=(char*)malloc(strlen(token)+1);
    // printf("you\n");
    strcpy(entry->value,value);
    strcpy(entry->token,token);
    return entry;
}
char* search(Table* table,char* value)
{
    // printf("yo");
    long long hashval=hashFunc(value);
    // printf("search hashval : %d\n",hashval);
    if(table->entries[hashval]!=NULL && strcmp(table->entries[hashval]->value,value)==0)
    return table->entries[hashval]->token;
    else
    return "/0";
}
void insert(Table* table,char* value,char* token)
{
    // printf("Ho");
    Entry*  item=createEntry(value,token);
    char* searchval = search(table,value);
    // printf("Searchval is : %s\n",searchval);
    if(strcmp(searchval,"/0")!=0){
        printf("Already there");
        return ;
    }
    // printf("insert value : %s, tok : %s\n",item->value,item->token);
    int hashval=hashFunc(value);
    // printf("hashval : %d\n",hashval);
    while(table->entries[hashval]!=NULL)
    {
        hashval=(hashval+1)%tableSize;
    }
    table->entries[hashval]=item;
    // printf("table entry token generated %s\n",table->entries[hashval]->token);
}

void populate_lookup_table() {
    // printf("hi\n");
  insert(symbol_table, "with",TOKEN_MAP[TK_WITH]);
    // printf("jj\n");
  insert(symbol_table, "parameters",TOKEN_MAP[TK_PARAMETERS]);
  insert(symbol_table, "end",TOKEN_MAP[TK_END]);
  insert(symbol_table, "while",TOKEN_MAP[TK_WHILE]);
  insert(symbol_table, "union",TOKEN_MAP[TK_UNION]);
  insert(symbol_table, "endunion",TOKEN_MAP[TK_ENDUNION]);
  insert(symbol_table, "definetype",TOKEN_MAP[TK_DEFINETYPE]);
  insert(symbol_table, "as",TOKEN_MAP[TK_AS]);
  insert(symbol_table, "type",TOKEN_MAP[TK_TYPE]);
  insert(symbol_table, "_main",TOKEN_MAP[TK_MAIN]);
  insert(symbol_table, "global",TOKEN_MAP[TK_GLOBAL]);
  insert(symbol_table, "parameter",TOKEN_MAP[TK_PARAMETER]);
  insert(symbol_table, "list",TOKEN_MAP[TK_LIST]);
  insert(symbol_table, "input",TOKEN_MAP[TK_INPUT]);
  insert(symbol_table, "output",TOKEN_MAP[TK_OUTPUT]);
  insert(symbol_table, "int",TOKEN_MAP[TK_INT]);
  insert(symbol_table, "real",TOKEN_MAP[TK_REAL]);
  insert(symbol_table, "endwhile",TOKEN_MAP[TK_ENDWHILE]);
  insert(symbol_table,"if",TOKEN_MAP[TK_IF]);
  insert(symbol_table,"then",TOKEN_MAP[TK_THEN]);
  insert(symbol_table,"endif",TOKEN_MAP[TK_ENDIF]);
  insert(symbol_table,"read",TOKEN_MAP[TK_READ]);
  insert(symbol_table,"write",TOKEN_MAP[TK_WRITE]);
  insert(symbol_table,"return",TOKEN_MAP[TK_RETURN]);
  insert(symbol_table,"call",TOKEN_MAP[TK_CALL]);
  insert(symbol_table,"record",TOKEN_MAP[TK_RECORD]);
  insert(symbol_table,"endrecord",TOKEN_MAP[TK_ENDRECORD]);
  insert(symbol_table,"else",TOKEN_MAP[TK_ELSE]);
}
#include "symbolTable.h"

// this function is used to find the hash value of the string
long long hashFunc(char* inp)
{
    //we use the rolling polynomial hash method with formula s[i]*p^i mod m
    int prime=53; //prime number close to number of alphabets(upper and lowercase)
    long long power=1;
    int modulo=1e5+3;//large prime number (probability of collision is 1/modulo)
    long long res=0;//final key value to be returned
    for(int i=0;i<strlen(inp);i++)
    {
        res=(((inp[i]-'a'+1)*power)+res)%modulo;
        power=(power*prime)%modulo;
    }
    return res;
}
//this function is to create the table and initialize all the entries to null
Table* createTable()
{
    Table* symTable;
    for(int i=0;i<tableSize;i++)
    {
        symTable->entries[i]=NULL;
    }
    return symTable;
}
// this function is to create an entry of the symbol table
Entry* createEntry(char* value,char* token)
{
    Entry* entry=(Entry*)malloc(sizeof(Entry));
    strcpy(entry->value,value);
    strcpy(entry->token,token);
    return entry;
}

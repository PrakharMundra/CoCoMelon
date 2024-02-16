#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define tableSize 1997
typedef struct Entry{
    char* value;
    char* token;
}Entry;
typedef struct Table{
    Entry* entries[tableSize];
}Table;

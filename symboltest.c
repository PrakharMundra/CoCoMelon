// #include "symbolTable.h"
#include "lexer.h"
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define int long long
// this function is used to find the hash value of the string


int main(){
    symbol_table = createTable();
    populate_lookup_table();
    char* st = search(symbol_table,"parameters");
    printf("%s\n",st);
}
#include "lexer.h"
// #include "symbolTable.h"
// #include "lexerDef.h"
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    FILE *fp = fopen("testfile.txt","r");
    lexer_init();
    removeComments("testfile.txt", "cleanfile.txt");
    while (buffer[forward] != EOF)
    {

        tkn tok;
        tok = getNextToken(fp);
        if (tok.name == "ERROR")
        {
            printf("Line no. %-5d ", tok.line);
            printf("Error : %s \n", tok.lexeme_value);
        }
        else if (tok.name == "TK_DELIM")
        {
            continue;
            // printf("Line no. %-10d ", tok.line);
            // printf("value = '%s' ", tok.lexeme_value);
            // printf("%s : %s \n", "token", tok.name);
        }
        else
        {
            printf("Line no. %-10d ", tok.line);
            if (tok.name == "TK_NUM")
                printf("value = %-10d ", tok.num);
            else if (tok.name == "TK_RNUM")
                printf("value = %-10.2e ", tok.rnum);
            else
                printf("value = %-10s ", tok.lexeme_value);
            printf("%s : %s \n", "token", tok.name);
        }
    }
}
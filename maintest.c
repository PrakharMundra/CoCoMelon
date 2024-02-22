#include "lexer.h"
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){

    lexer_init();
    FILE * fp = fopen("testfile.txt","r");
    // printf("%f\n",atof("2.35"));
    while(buffer[forward]!=EOF){
        
        tkn test;
        test = getNextToken(fp);
        if(test.name==TK_DELIM) continue;
        else if(test.name==TK_NUM) printf("num = %d\n",test.num);
        else if(test.name==TK_RNUM) printf(" rnum = %f\n",test.rnum);
        else printf("value = '%s'\n", test.lexeme_value);
        printf("state in main after dfa: %d, %c, line no. %d\n\n",state,buffer[forward-1], test.line);
    }



}
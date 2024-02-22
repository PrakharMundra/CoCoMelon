#include "lexerDef.h"
#include "lexer.h"
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//retraction function
void retract(int num) {
  
  forward -= num;
  if (forward < 0) {
    forward += BUFFER_SIZE;
  }
  retraction+=num;
}
//initialize function
void lexer_init(){
    forward=0;
    lexemeBegin=0;
    line1=1;
    for(int i=0;i<4096;i++){
        buffer[i]='\0';
    }
    state=0;
    retraction=0; 

}
//finding the length of the lexeme 
int get_len(){
    if(lexemeBegin<=forward){
        return forward-lexemeBegin;
    }
    else{
        // return BUFFER_SIZE + lexemeBegin-forward;
        return forward +  BUFFER_SIZE - lexemeBegin;
    }
}
// getting the name of the lexeme
char* get_name(){
    int len=get_len();
    // printf("The length taken %d\n",len);
    char* lexeme= malloc(len+1);
    int start=lexemeBegin;
    int i=0;
    while(start%BUFFER_SIZE!=forward){
        lexeme[i]=buffer[start%BUFFER_SIZE];
        // printf("  %c, %c \n",buffer[start%BUFFER_SIZE], lexeme[i]);
        // printf("  %c  ",lexeme[i]);

        start++;
        i++;
    }
   
    lexeme[len]='\0';
    
    return lexeme;
}
// This function basically fills the twin buffer and returns character to check on dfa
char getChar(FILE* fp){
    if(forward==BUFFER_SIZE)forward=0;
    if(forward==0||forward==BUFFER_SIZE/2){
        if(retraction==0){
        int num=fread(&buffer[forward],1,BUFFER_SIZE/2,fp);
        if(num<BUFFER_SIZE/2){
            buffer[forward+num]=EOF;
        }
        }
    }
    char c=buffer[forward];
    forward++;
    if(retraction>0){
        retraction--;
    }
    return c;
}
// the basic function which simulates the dfa and returns the token to syntax analyser
tkn getNextToken(FILE* fp){
    
    tkn token;
    token.line=line1;
    state = 0;

    while(true){
        switch(state){
            case 0:;
            char c=getChar(fp);
            // printf("char taken : %c\n",c);
            if(c=='<'){
                state=1;
            }
            else if(c=='\n'){
                state=57;
            }
            else if(c==' '||c=='\t'){
                state=58;

            }
            else if(c=='!'){
                state=55;
            }
            else if(c=='#'){
                state=26;
            }
            else if(c=='_'){
                state=22;
            }
            else if(c=='%'){
                state=6;
            }
            else if(c==')'){
                state=36;
            }
            else if(c=='('){
                state=35;

            }
            else if(c=='.'){
                state=34;
            }
            else if(c==':'){
                state=33;
            }
            else if(c==';'){
                state=32;
            }
            else if(c==','){
                state=31;
            }
            else if(c==']'){
                state=30;
            }
            else if(c=='['){
                state=29;
            }
            else if(c=='+'){
                state=37;
            }
            else if(c=='-'){
                state=38;
            }
            else if(c=='*'){
                state=39;
            }
            else if(c=='/'){
                state=40;
            }
            else if(c=='&'){
                state=41;
            }
            else if(c=='@'){
                state=44;
            }
            else if(c=='~'){
                state=47;
            }
            else if(c=='='){
                state=48;
            }
            else if(c=='>'){
                state=50;
            }
            else if((c=='a')||(((int)(c-'a'))>=4  && (int)(c-'a')<26)){
                state=7;
            }
            else if(((int)(c-'a'))>=1&&((int)(c-'a'))<=3){
                state=9;
            }
            else if(((int)(c-'0')>=0) &&((int)(c-'0'))<=9){
                state=13;
                // printf("Reached state13");
            }
            else{
                // retract(1);
                printf("\nerror in state %d",state);
                token.name=ERROR;
                lexemeBegin=(forward)%(BUFFER_SIZE);
                return token;
                
            }
            break;

            case 1:;
             c=getChar(fp);
            if(c=='-'){
                state=2;

            }
            else if(c=='='){
                state=54;

            
            }
            else {
                state=53;

            }
            break;
            case 2:;
             c=getChar(fp);
            if(c=='-'){
                state=3;
            }
            else{
                state=5;
            }
            break;
            case 3:;
             c=getChar(fp);
            if(c=='-'){
                state=4;
            }
            else{
                retract(1);
                printf("\nerror in state %d",state);
                token.name=ERROR;
                lexemeBegin=(forward)%(BUFFER_SIZE);
                
                return token;
            }
            break;
            case 4:;
            token.name=TK_ASSIGNOP;
            token.lexeme_value="<---";
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            break;
            case 5:;
            retract(2);
            token.name=TK_LT;
            token.lexeme_value="<";
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            case 6:;
            c=getChar(fp);
            if(c=='\n'){
                state=60;
            }
            else{
                state=6;
            }
            break;
            case 7:;
            c=getChar(fp);
            if(((int)(c-'a')>=0)&&((int)(c-'a')<26)){
                state=7;

            }
            else{
                state=8;
            }
            break;
            case 8:;
            retract(1);
            

            token.name=TK_FIELDID;
            token.lexeme_value=get_name();
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            break;
            case 9:;
            c=getChar(fp);
            if(((int)(c-'a')>=0)&&((int)(c-'a')<26)){
                state=7;

            }
            else if(((int)(c-'2')>=0)&&((int)(c-'2')<=5)){
                state=10;
            }
            else{
                //printf("\nerror in state %d",state);
                token.name=ERROR;
                lexemeBegin=(forward)%(BUFFER_SIZE);
                return token ;
            }
            break;
            case 10:;
            c=getChar(fp);
            if(((int)(c-'a'))>=1&&((int)(c-'a'))<=3){
                state=10;
            }
            else if(((int)(c-'2')>=0)&&((int)(c-'2')<=5)){
                state=12;
            }
            else{
                state=11;
            }
            break;
            case 11:;
            retract(1);
            int ln=get_len();
            if(ln<2||ln>20){
                printf("\nerror in state %d",state);
                token.name=ERROR;
                lexemeBegin=(forward)%(BUFFER_SIZE);
                return token;
            }
            

            token.name=TK_ID;

            token.lexeme_value=get_name();
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            break;

            case 12:;
            c=getChar(fp);
            if(((int)(c-'2')>=0)&&((int)(c-'2')<=5)){
                state=12;
            }
            else{
                state=11;
            }
            break;
            case 13:;
            c=getChar(fp);
            //printf("hello");
            if((c-'0')>=0&&(c-'0')<=9){
                state=13;
            }
            else if(c=='.'){
                
                state=15;
            }
            else{
                state=14;
            }
            break;
            case 14:;
            retract(1);
            token.name=TK_NUM;

            token.num=atoi(get_name());
            lexemeBegin=(forward)%(BUFFER_SIZE);
            // printf("Reached state 14\n");
            return token;
            break;
            case 15:;
            c=getChar(fp);
            //printf("reached ");
            if((c-'0')>=0&&(c-'0')<=9){
                state=16;
            }
            else{
                state=21;

            }
            case 16:;
            //printf("state16");
            c=getChar(fp);
            //printf("   char read  %c   ",c);
            // printf("\n   c-'0' = %d, isdigit() = %d   \n",c-'0',isdigit(c-'0'));
            if((c-'0')>=0&&(c-'0')<=9){
                state=17;
            }
            else{
                retract(1);
                printf("\nerror in state %d",state);
                token.name=ERROR;
                lexemeBegin=(forward)%(BUFFER_SIZE);
                return token;
            }
            case 17:;
            printf("state17 ");
            c=getChar(fp);
            if(c=='E'){
                state=18;


            }
            else{
                state=61;
                printf("st.61\n");
                printf("%s\n",get_name());
                

            }
            break;
            case 61:;
            retract(1);
            printf("st.61\n");
                token.name=TK_RNUM;
                
                token.rnum=atof(get_name());
                 lexemeBegin=(forward)%(BUFFER_SIZE);
                 return token;
                 break;

            case 62:;
            printf("st.62\n");
                token.name=TK_RNUM;
                
                token.rnum=atof(get_name());
                 lexemeBegin=(forward)%(BUFFER_SIZE);
                 return token;
                 break;

            case 18:;
            printf("st.18\n");
            c=getChar(fp);
            // printf("%c",c);
            if((c-'0')>=0&&(c-'0')<=9){
                state=20;
            }
            else if(c=='+'||c=='-'){
                state=19;
            }
            else {
                retract(1);
                printf("\nerror in state %d",state);
                token.name=ERROR;
                lexemeBegin=(forward)%(BUFFER_SIZE);
                return token;
            }
            break;
            case 19:;
            c=getChar(fp);
            printf("st.19\n");
            if((c-'0')>=0&&(c-'0')<=9){
                state=20;
            }
            else{
                retract(1);
                printf("\nerror in state %d",state);
                token.name=ERROR;
                lexemeBegin=(forward)%(BUFFER_SIZE);

                return token;

            }
            break;
            case 20:;
            printf("st.20\n");
            c=getChar(fp);
            if((c-'0')>=0&&(c-'0')<=9){
                state=62;
                printf("%s",get_name());
            }
            else{
                retract(1);
                printf("\nerror in state %d",state);
                token.name=ERROR;
                lexemeBegin=(forward)%(BUFFER_SIZE);

                return token;

            }
            break;
            case 21:;
            retract(2);
            token.name=TK_NUM;

            token.num=atoi(get_name());
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            break;
            case 22:;
            c=getChar(fp);
            if(isalpha(c)!=0){
                state=23;
            }
            else{
                retract(1);
                printf("\nerror in state %d",state);
                token.name=ERROR;
                lexemeBegin=(forward)%(BUFFER_SIZE);

                return token;
            }
            break;
            case 23:;
            c=getChar(fp);
            if(isalpha(c)!=0){
                state=23;
            }
            else if((c-'0')>=0&&(c-'0')<=9){
                state=25;
            }
            else{
                state=24;
            }
            break;
            case 24:;
            retract(1);
            ln=get_len();
            if(ln>30){
                retract(1);
                printf("\nerror in state %d",state);
                token.name=ERROR;
                lexemeBegin=(forward)%(BUFFER_SIZE);
                
                return token;
            }
            else{
                token.name=TK_FUNID;
                token.lexeme_value=get_name();
                lexemeBegin=(forward)%(BUFFER_SIZE);
                return token;

            }
            case 25:;
            c=getChar(fp);
            if(((c-'0')>=0)&&((c-'0')<=9)){
                state=25;
            }
            else{
                state=24;
            }
            break;
            case 26:;
            c=getChar(fp);
            if((((int)(c-'a'))>=0)&&(((int)(c-'a'))<26)){
                state=27;

            }
            else{
                retract(1);
                printf("\nerror in state %d",state);
                token.name=ERROR;
                lexemeBegin=(forward)%(BUFFER_SIZE);
                return token;
            }
            break;
            case 27:;
            c=getChar(fp);
            if((((int)(c-'a'))>=0)&&(((int)(c-'a'))<26)){
                state=27;

            }
            else{
                state=28;
            }
            break;
            case 28:;
            retract(1);
            token.name=TK_RUID;
            token.lexeme_value=get_name();
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            case 29:;
            token.name=TK_SQL;
            token.lexeme_value="[";
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            case 30:;
            token.name=TK_SQR;
            token.lexeme_value="]";
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            case 31:;
            token.name=TK_COMMA;
            token.lexeme_value=",";
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            case 32:;
            token.name=TK_SEM;
            token.lexeme_value=";";
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            case 33:;
            token.name=TK_COLON;
            token.lexeme_value=":";
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            case 34:;
            token.name=TK_DOT;
            token.lexeme_value=".";
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            case 35:;
            token.name=TK_OP;
            token.lexeme_value="(";
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            case 36:;
            token.name=TK_CL;
            token.lexeme_value=")";
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            case 37:;
            token.name=TK_PLUS;
            token.lexeme_value="+";
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            case 38:;
            token.name=TK_MINUS;
            token.lexeme_value="-";
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            case 39:;
            token.name=TK_MUL;
            token.lexeme_value="*";
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            case 40:;
            token.name=TK_DIV;
            token.lexeme_value="/";
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            case 41:;
            c=getChar(fp);
            if(c=='&'){
                state=42;
            }
            else{
                retract(1);
                printf("\nerror in state %d",state);
                token.name=ERROR;
                lexemeBegin=(forward)%(BUFFER_SIZE);
                return token;
            }
            break;
            case 42:;
            c=getChar(fp);
            if(c=='&'){
                state=43;
            }
            else{
                retract(1);
                printf("\nerror in state %d",state);
                token.name=ERROR;
                lexemeBegin=(forward)%(BUFFER_SIZE);
                return token;
            }
            break;
            case 43:;
            token.name=TK_AND;
            token.lexeme_value="&&&";
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            case 44:;
            c=getChar(fp);
            if(c=='@'){
                state=45;
            }
            else{
                retract(1);
                printf("\nerror in state %d",state);
                token.name=ERROR;
                lexemeBegin=(forward)%(BUFFER_SIZE);
                return token;
            }
            break;
            case 45:;
            c=getChar(fp);
            if(c=='@'){
                state=46;
            }
            else{
                retract(1);
                printf("\nerror in state %d",state);
                token.name=ERROR;
                lexemeBegin=(forward)%(BUFFER_SIZE);
                return token;
            }
            break;
            case 46:;
            token.name=TK_OR;
            token.lexeme_value="@@@";
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            case 47:;
            token.name=TK_NOT;
            token.lexeme_value="~";
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            case 48:;
            c=getChar(fp);
            if(c=='='){
                state=49;
            }
            else{
                retract(1);
                printf("\nerror in state %d",state);
                token.name=ERROR;
                lexemeBegin=(forward)%(BUFFER_SIZE);
                return token;
            }
            break;
            case 49:;
            token.name=TK_EQ;
            token.lexeme_value="==";
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            case 50:;
            c=getChar(fp);
            if(c=='='){
                state=52;

            }
            else{
                state=51;
            }
            break;
            case 51:;
            retract(1);
            token.name=TK_GT;
            token.lexeme_value=">";
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            case 52:;
            // retract(1);
            token.name=TK_GE;
            token.lexeme_value=">=";
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            case 53:;
            retract(1);
            token.name=TK_LT;
            token.lexeme_value="<";
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            case 54:;
            token.name=TK_LE;
            token.lexeme_value="<=";
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            case 55:;
            c= getChar(fp);
            if(c=='='){
                state=56;
            }
            else{
                retract(1);
                printf("\nerror in state %d",state);
                token.name=ERROR;
                lexemeBegin=(forward)%(BUFFER_SIZE);
                return token;

            }
            break;
            case 56:;
            token.name=TK_LE;
            token.lexeme_value="!=";
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            case 57:;
            token.name = TK_DELIM;
            line1++;
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;
            case 58:;
            c=getChar(fp);
            if(c==' '||c=='\t'){
                state=58;
            }
            else{
                state=59;
            }
            break;
            case 59:;
            retract(1);
            token.name = TK_DELIM;
            lexemeBegin=(forward)%(BUFFER_SIZE);
            return token;

            case 60:;
            token.name=TK_COMMENT;
            token.lexeme_value="COMMENT";
            lexemeBegin=(forward)%(BUFFER_SIZE);
            line1++;
            return token;
            

        }
    }
}


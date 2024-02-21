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
    line_no=1;
    for(int i=0;i<4096;i++){
        buffer[i]='\0';
    }
    state=0;
    retraction=0; 

}
//finding the length of the lexeme 
int get_len(){
    if(lexemeBegin<=forward){
        return forward-lexemeBegin+1;
    }
    else{
        return BUFFER_SIZE + lexemeBegin-forward+1;

    }
}
// getting the name of the lexeme
char* get_name(){
    int len=get_len();
    char* lexeme= malloc(len+1);
    int start=lexemeBegin;
    int i=0;
    while(start%BUFFER_SIZE!=forward){
        lexeme[i]=buffer[start];
        start++;
        i++;
    }
    lexeme[len-1]=buffer[start];
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
    token.line_no=line_no;
    
    while(true){
        
        switch(state){
            case 0:
            char c=getChar(fp);
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
            else if(((int)(c-'a'))<1||((int)(c-'a'))>4){
                state=7;
            }
            else if(((int)(c-'a'))>=1||((int)(c-'a'))<=3){
                state=9;
            }
            else if(((int)(c-'0'))<=9){
                state=13;
            }
            else{
                print("Error");
                token.name=ERROR;
                lexemeBegin=(forward+1)%(BUFFER_SIZE);
                return token;
                
            }
            break;

            case 1:
            char c=getChar(fp);
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
            case 2:
            char c=getChar(fp);
            if(c=='-'){
                state=3;
            }
            else{
                state=5;
            }
            break;
            case 3:
            char c=getChar(fp);
            if(c=='-'){
                state=4;
            }
            else{
                print("Error");
                token.name=ERROR;
                lexemeBegin=(forward+1)%(BUFFER_SIZE);
                
                return token;
            }
            break;
            case 4:
            token.name=TK_ASSIGNOP;
            token.lexeme_value="<---";
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            break;
            case 5:
            retract(2);
            token.name=TK_LT;
            token.lexeme_value="<";
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            case 6:
            char c=getChar(fp);
            if(c=='\n'){
                state=60;
            }
            else{
                state=6;
            }
            break;
            case 7:
            char c=getChar(fp);
            if(((int)(c-'a')>=0)&&((int)(c-'a')<26)){
                state=7;

            }
            else{
                state=8;
            }
            break;
            case 8:
            retract(1);
            

            token.name=TK_FIELDID;
            token.lexeme_value=get_name();
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            break;
            case 9:
            char c=getChar(fp);
            if(((int)(c-'a')>=0)&&((int)(c-'a')<26)){
                state=7;

            }
            else if(((int)(c-'2')>=0)&&((int)(c-'2')<=5)){
                state=10;
            }
            else{
                printf("ERROR");
                token.name=ERROR;
                lexemeBegin=(forward+1)%(BUFFER_SIZE);
                return token ;
            }
            break;
            case 10:
            char c=getChar(fp);
            if(((int)(c-'a'))>=1||((int)(c-'a'))<=3){
                state=10;
            }
            else if(((int)(c-'2')>=0)&&((int)(c-'2')<=5)){
                state=12;
            }
            else{
                state=11;
            }
            break;
            case 11:
            retract(1);
            int ln=get_len();
            if(ln<2||ln>20){
                print("error");
                token.name=ERROR;
                lexemeBegin=(forward+1)%(BUFFER_SIZE);
                return token;
            }
            

            token.name=TK_ID;

            token.lexeme_value=get_name();
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            break;

            case 12:
            char c=getChar(fp);
            if(((int)(c-'2')>=0)&&((int)(c-'2')<=5)){
                state=12;
            }
            else{
                state=11;
            }
            break;
            case 13:
            char c=getChar(fp);
            if(isdigit(c)!=0){
                state=13;
            }
            else if(c=='.'){
                state=15;
            }
            else{
                state=14;
            }
            break;
            case 14:
            retract(1);
            token.name=TK_NUM;

            token.num=atoi(get_name());
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            break;
            case 15:
            char c=getChar(fp);
            if(isdigit(c)!=0){
                state=16;
            }
            else{
                state=21;

            }
            case 16:
            char c=getChar(fp);
            if(isdigit(c)!=0){
                state=17;
            }
            else{
                print("ERROR");
                token.name=ERROR;
                lexemeBegin=(forward+1)%(BUFFER_SIZE);
                return token;
            }
            case 17:
            char c=getChar(fp);
            if(c=='E'){
                state=18;


            }
            else{
                state=61;
                

            }
            break;
            case 61:
            retract(1);
                token.name=TK_RNUM;
                token.num=atof(get_name());
                 lexemeBegin=(forward+1)%(BUFFER_SIZE);
                 return token;
                 break;
            case 18:
            char c=getChar(fp);
            if(isdigit(c)!=0){
                state=20;
            }
            else if(c=='+'||c=='-'){
                state=19;
            }
            else {
                print("ERROR");
                token.name=ERROR;
                lexemeBegin=(forward+1)%(BUFFER_SIZE);
                return token;
            }
            break;
            case 19:
            char c=getChar(fp);
            if(isdigit(c)!=0){
                state=20;
            }
            else{
                print("ERROR");
                token.name=ERROR;
                lexemeBegin=(forward+1)%(BUFFER_SIZE);

                return token;

            }
            break;
            case 20:
            char c=getChar(fp);
            if(isdigit(c)!=0){
                state=61;
            }
            else{
                print("ERROR");
                token.name=ERROR;
                lexemeBegin=(forward+1)%(BUFFER_SIZE);

                return token;

            }
            case 21:
            retract(2);
            token.name=TK_NUM;

            token.num=atoi(get_name());
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            break;
            case 22:
            char c=getChar(fp);
            if(isalpha(c)!=0){
                state=23;
            }
            else{
                printf("ERROR");
                token.name=ERROR;
                lexemeBegin=(forward+1)%(BUFFER_SIZE);

                return token;
            }
            break;
            case 23:
            char c=getChar(fp);
            if(isalpha(c)!=0){
                state=23;
            }
            else if(isdigit(c)!=0){
                state=25;
            }
            else{
                state=24;
            }
            break;
            case 24:
            retract(1);
            int ln=get_len();
            if(ln>30){
                printf("Error");
                token.name=ERROR;
                lexemeBegin=(forward+1)%(BUFFER_SIZE);
                
                return token;
            }
            else{
                token.name=TK_FUNID;
                token.lexeme_value=get_name();
                return token;

            }
            case 25:
            char c=getChar(fp);
            if(isdigit(c)!=0){
                state=25;
            }
            else{
                state=24;
            }
            break;
            case 26:
            char c=getChar(fp);
            if((((int)(c-'a'))>=0)&&(((int)(c-'a'))<26)){
                state=27;

            }
            else{
                printf("Error");
                token.name=ERROR;
                lexemeBegin=(forward+1)%(BUFFER_SIZE);
                return token;
            }
            break;
            case 27:
            char c=getChar(fp);
            if((((int)(c-'a'))>=0)&&(((int)(c-'a'))<26)){
                state=27;

            }
            else{
                state=28;
            }
            break;
            case 28:
            retract(1);
            token.name=TK_RUID;
            token.lexeme_value=get_name();
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            case 29:
            token.name=TK_SQL;
            token.lexeme_value="[";
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            case 30:
            token.name=TK_SQR;
            token.lexeme_value="]";
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            case 31:
            token.name=TK_COMMA;
            token.lexeme_value=",";
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            case 32:
            token.name=TK_SEM;
            token.lexeme_value=";";
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            case 33:
            token.name=TK_COLON;
            token.lexeme_value=":";
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            case 34:
            token.name=TK_DOT;
            token.lexeme_value=".";
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            case 35:
            token.name=TK_OP;
            token.lexeme_value="(";
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            case 36:
            token.name=TK_CL;
            token.lexeme_value=")";
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            case 37:
            token.name=TK_PLUS;
            token.lexeme_value="+";
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            case 38:
            token.name=TK_MINUS;
            token.lexeme_value="-";
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            case 39:
            token.name=TK_MUL;
            token.lexeme_value="*";
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            case 40:
            token.name=TK_DIV;
            token.lexeme_value="/";
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            case 41:
            char c=getChar(fp);
            if(c=="&"){
                state=42;
            }
            else{
                printf("ERROR");
                token.name=ERROR;
                lexemeBegin=(forward+1)%(BUFFER_SIZE);
                return token;
            }
            break;
            case 42:
            char c=getChar(fp);
            if(c=="&"){
                state=43;
            }
            else{
                printf("ERROR");
                token.name=ERROR;
                lexemeBegin=(forward+1)%(BUFFER_SIZE);
                return token;
            }
            break;
            case 43:
            token.name=TK_AND;
            token.lexeme_value="&&&";
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            case 44:
            char c=getChar(fp);
            if(c=="@"){
                state=45;
            }
            else{
                printf("ERROR");
                token.name=ERROR;
                lexemeBegin=(forward+1)%(BUFFER_SIZE);
                return token;
            }
            break;
            case 45:
            char c=getChar(fp);
            if(c=="@"){
                state=46;
            }
            else{
                printf("ERROR");
                token.name=ERROR;
                lexemeBegin=(forward+1)%(BUFFER_SIZE);
                return token;
            }
            break;
            case 46:
            token.name=TK_OR;
            token.lexeme_value="@@@";
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            case 47:
            token.name=TK_NOT;
            token.lexeme_value="~";
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            case 48:
            char c=getChar(fp);
            if(c=="="){
                state=49;
            }
            else{
                printf("ERROR");
                token.name=ERROR;
                lexemeBegin=(forward+1)%(BUFFER_SIZE);
                return token;
            }
            break;
            case 49:
            token.name=TK_EQ;
            token.lexeme_value="==";
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            case 50:
            char c=getChar(fp);
            if(c=="="){
                state=52;

            }
            else{
                state=51;
            }
            break;
            case 51:
            retract(1);
            token.name=TK_GT;
            token.lexeme_value=">";
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            case 52:
            retract(1);
            token.name=TK_GE;
            token.lexeme_value=">=";
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            case 53:
            retract(1);
            token.name=TK_LT;
            token.lexeme_value="<";
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            case 54:
            token.name=TK_LE;
            token.lexeme_value="<=";
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            case 55:
            char c= getChar(fp);
            if(c=="="){
                state=56;
            }
            else{
                printf("ERROR");
                token.name=ERROR;
                lexemeBegin=(forward+1)%(BUFFER_SIZE);
                return token;

            }
            break;
            case 56:
            token.name=TK_LE;
            token.lexeme_value="<=";
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            case 57:
            line_no++;
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return ;
            case 58:
            char c=getChar(fp);
            if(c==" "||c=="\t"){
                state=58;
            }
            else{
                state=59;
            }
            break;
            case 59:
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            return token;
            case 60:
            token.name=TK_COMMENT;
            lexemeBegin=(forward+1)%(BUFFER_SIZE);
            line_no++;
            return token;
            



























            









            











        }
    }
}



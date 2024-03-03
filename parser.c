
#include "parser.h"
#define max_len 256

void populate()
{
    char buffer[max_len];
    FILE* fp=fopen("grammar.txt","r");
    if(fp==NULL)
    {
        printf("Error opening file");
        return;
    }
    int ruleno=-1;
    while(fgets(buffer,max_len,fp))
    {
        ruleno++;
        int x=0;
        int rulesize=-1;
        char* sym;
        sym=(char*) malloc(40*sizeof(char));
        for(int i=0;i<strlen(buffer);i++)
        {
            // printf("%c",buffer[i]);
            if(buffer[i]!=' ' && buffer[i]!='.')
            {
                sym[x]=buffer[i];
                // printf("%c", sym[x]);
                x++;
            }
            else
            {
                // printf("%s",sym);
                rulesize++;
                sym[x]='\0';
                if(sym[0]=='T')
                {
                    for(int j=0;j<sizeof(Terminals);j++){
                       if (strcmp(sym,Terminals[j])==0)
                       {
                        Grammar[ruleno].rule[rulesize].isTerminal=true;
                        Grammar[ruleno].rule[rulesize].t=j;
                        break;
                       }
                    }
                }
                else
                {
                    for(int j = 0;j<sizeof(nonTerminals);j++){
                        
                        if(strcmp(sym,nonTerminals[j])==0){
                            Grammar[ruleno].rule[rulesize].isTerminal = false;
                            Grammar[ruleno].rule[rulesize].nt = j;
                            break;
                        }
                    }
                }
                x=0;
                free(sym);
                sym=(char*) malloc(20*sizeof(char));
            }
            Grammar[ruleno].len=rulesize;
        }

    }
    fclose(fp);
    // printf("Populated");
}
void first_set(gSym x){
    //printf("Hello");
    for(int i=0;i<MAX_SIZE;i++){
         int flag=0;
        if(Grammar[i].rule[0].nt==x.nt)
        {  //printf("%s ",nonTerminals[x.nt]);
            
            for(int j=1;j<=Grammar[i].len;j++){
                if(Grammar[i].rule[j].isTerminal==true){
                    //printf("Hola");
                    if(strcmp(Terminals[Grammar[i].rule[j].t],"TK_EPS")==0){
                        int f=0;
                        for(int k=0;k<firstSet[x.nt].size;k++){
                            if(firstSet[x.nt].set[k].t==Grammar[i].rule[j].t){
                                f=1;
                                break;
                            }
                        }
                            if(f==0){
                                firstSet[x.nt].set[firstSet[x.nt].size]=Grammar[i].rule[j];
                                firstSet[x.nt].size++;

                            }            
                        break;

                    }
                    else{
                        //printf("%s ",Terminals[Grammar[i].rule[j].t]);
                        
                        int f=0;
                        for(int k=0;k<firstSet[x.nt].size;k++){
                            if(firstSet[x.nt].set[k].t==Grammar[i].rule[j].t){
                                f=1;
                                break;
                            }
                        }
                            if(f==0){
                                firstSet[x.nt].set[firstSet[x.nt].size]=Grammar[i].rule[j];
                                firstSet[x.nt].size++;
                            }
                        break; 
                }
                }
                else{
                    first_set(Grammar[i].rule[j]);
                    gSym first=Grammar[i].rule[j];        
                    for(int k=0;k<firstSet[first.nt].size;k++){
                        int f=0;
                        if(firstSet[first.nt].set[k].t==TK_EPS){
                                flag=1;
                                continue;

                            }
                        for(int l=0;l<firstSet[x.nt].size;l++){
                            
                            if(firstSet[x.nt].set[l].t==firstSet[first.nt].set[k].t){
                                f=1;
                                break;
                            }
                        }
                            if(f==0){
                                firstSet[x.nt].set[firstSet[x.nt].size]=firstSet[first.nt].set[k];
                                firstSet[x.nt].size++;

                            }
                    }
                    if(flag==0){
                        break;
                    }   
                }
            } 
            if(flag==1){
                gSym eps;
                eps.isTerminal=true;
                eps.t=TK_EPS;
                firstSet[x.nt].set[firstSet[x.nt].size]=eps;
            }
            visitedFirst[x.nt]=1;
        }
    }
}
void ComputeFirstAndFollowSet(){
    for(int i=0;i<NT_SIZE;i++){
        if(visitedFirst[i]==1)continue;
        gSym x;
        x.isTerminal=false;
        x.nt=i;
        first_set(x);   
    }
    while(true){
        int change=0;
    for(int i=0;i<NT_SIZE;i++){
        gSym x;
        x.isTerminal=false;
        x.nt=i;
        int check=0;
        for(int j=0;j<MAX_SIZE;j++){
            
            for(int k=1;k<=Grammar[j].len;k++){
                int flag=0;
                if(Grammar[j].rule[k].isTerminal==false&&(Grammar[j].rule[k].nt==x.nt)){
                    check=1;
                    if(k==Grammar[j].len){
                        flag=1;
                    }
                    else{
                        if((Grammar[j].rule[k+1].isTerminal==true)){
                            flag=0;
                            int c=0;
                            for(int l=0;l<followSet[x.nt].size;l++){
                                if(followSet[x.nt].set[l].t==Grammar[j].rule[k+1].t){
                                    c=1;
                                    break;
                                }
                            }
                            if(c==0){
                                change++;
                                followSet[x.nt].set[followSet[x.nt].size]=Grammar[j].rule[k+1];
                                followSet[x.nt].size++;
                            }
                        }
                        else{
                            for(int l=k+1;l<=Grammar[j].len;l++){
                                //int f=0;
                                gSym follow=Grammar[j].rule[l];
                                if(follow.isTerminal==true){
                                       flag=0;         
                                        //f=0;
                                        int c=0;
                                        for(int m=0;m<followSet[x.nt].size;m++){
                                        if(followSet[x.nt].set[m].t==follow.t){
                                        c=1;
                                        break;
                                        }
                                        }
                                        if(c==0){
                                        change++;
                                        followSet[x.nt].set[followSet[x.nt].size]=follow;
                                        followSet[x.nt].size++;
                                       }
                                       break;      
                                }
                                else{
                                    int g=0;
                                    //int f=0;
                                    for(int m=0;m<firstSet[follow.nt].size;m++){
                                        gSym term=firstSet[follow.nt].set[m];
                                        if(term.t==TK_EPS){
                                            g=1;
                                            continue;
                                        }
                                        else{
                                            int c=0;
                                            for(int n=0;n<followSet[x.nt].size;n++){
                                                if(term.t==followSet[x.nt].set[n].t){
                                                    c=1;
                                                    break;
                                                }
                                            }
                                            if(c==0){
                                                change++;
                                                followSet[x.nt].set[followSet[x.nt].size]=term;
                                                followSet[x.nt].size++;
                                            }
                                        }
                                    }
                                    if(g==0){
                                        flag=0;
                                        break;
                                    }
                                    else{
                                        flag=1;
                                    }
                                }                        
                            }
                        }
                    }
                    if(flag==1){
                        gSym term=Grammar[j].rule[0];
                        for(int m=0;m<followSet[term.nt].size;m++){
                                        gSym add=followSet[term.nt].set[m];                                  
                                            int c=0;
                                            for(int n=0;n<followSet[x.nt].size;n++){
                                                if(add.t==followSet[x.nt].set[n].t){
                                                    c=1;
                                                    break;
                                                }
                                            }
                                            if(c==0){
                                                change++;
                                                followSet[x.nt].set[followSet[x.nt].size]=add;
                                                followSet[x.nt].size++;
                                            }                                    
                                    }
                    }
                }                
            }
        }
        if(check==0){
            int c=0;
            gSym dollar;
            dollar.isTerminal=true;
            dollar.t=TK_DOLLAR;
            for(int m=0;m<followSet[x.nt].size;m++){
                if(followSet[x.nt].set[m].t==TK_DOLLAR){
                    c=1;
                    break;
                }
            }
            if(c==0){
                change++;
                followSet[x.nt].set[followSet[x.nt].size]=dollar;
                followSet[x.nt].size++;
            }
        } 
    }
    if(change==0)break;
    }
}

void createParseTable()
{
    for(int i=0;i<MAX_SIZE;i++)
    {
        Rule r=Grammar[i];
        int flag1=0;
        for(int j=1;j<=r.len;j++){
            flag1=0;
            gSym g=r.rule[j];
            if(g.isTerminal==true && g.t!=TK_EPS)
            {
                ParseTable[r.rule[0].nt][g.t]=r;
                break;
            }
            else if(g.isTerminal==false)
            {
                for(int k=0;k<firstSet[g.nt].size;k++)
                {
                    if(firstSet[g.nt].set[k].t==TK_EPS)
                    {
                        flag1=1;
                        continue;
                    }
                    else
                    {
                        ParseTable[r.rule[0].nt][firstSet[g.nt].set[k].t]=r;
                    }
                }
                if(flag1==0)
                break;
            }
            else
            {
                flag1=1;
                break;
            }
        } 
        if(flag1==1)
        {
            for(int k=0;k<followSet[r.rule[0].nt].size;k++)
            {
                ParseTable[r.rule[0].nt][followSet[r.rule[0].nt].set[k].t]=r;
            }
        }
    }
    for(int i=0;i<NT_SIZE;i++)
    {
        for(int j=0;j<followSet[i].size;j++)
        {
            if(ParseTable[i][followSet[i].set[j].t].len==0)
            {
                ParseTable[i][followSet[i].set[j].t].synch=true;
            }
        }
    }
}
void generateParseTree(char* fileName)
{
    FILE *fp = fopen(fileName,"r");
    lexer_init();
    create_stack();
    int flag=0;
    while (buffer[forward] != EOF)
    {
        if(isEmpty(s))
        {
            printf("Stack is Empty and there is problem in FILE");
            break;
        }
        struct tokeninfo tok;
        if(flag==0)
        {
        tok=getNextToken(fp);
        }
        gSym temp =top(s);
        if(temp.isTerminal==true)
        {
            if(tok.name==temp.t)
            {
                pop(s);
                flag=0;
            }
            else
            {
                printf("Error terminals dont match");
                pop(s);
                flag=0;
            }
        }
        else
        {
            if(ParseTable[temp.nt][tok.name].len!=0)
            {
                pop(s);
                for(int i=ParseTable[temp.nt][tok.name].len;i>=1;i--)
                {
                    push(s,ParseTable[temp.nt][tok.name].rule[i]);
                }
                flag=1;
            }
            else if(ParseTable[temp.nt][tok.name].synch==true)
            {
                pop(s);
                flag=1;
            }
            else
            {
                printf("ERROR");
                flag=0;
            }
        }
}
}
int main()
{
    populate();
    // //compute_first_set();
    ComputeFirstAndFollowSet();
    createParseTable();
    
    // for(int i=0;i<NT_SIZE;i++)
    // {
    //     for(int j=0;j<T_SIZE-1;j++)
    //     {
    //         if(ParseTable[i][j].len!=0)
    //         {
    //         printf("%s %s ",nonTerminals[i],Terminals[j]);
    //         printf("%d \n",ParseTable[i][j].len);
    //         }
    //     }
    // }

}

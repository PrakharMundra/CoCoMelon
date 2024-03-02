#include "parserDef.h"
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
                    // printf("test3");
                }
                x=0;
                free(sym);
                sym=(char*) malloc(20*sizeof(char));
                    // printf("test4");
            }
            
            Grammar[ruleno].len=rulesize;
        }

    }
    fclose(fp);
}
void ComputeFirstAndFollowSet(){
    for(int i=0;i<NT_SIZE;i++){
        if(visitedFirst[i]==1)continue;
        gSym x;
        x.isTerminal=false;
        x.nt=i;

       
        //printf("Hi");
        //int epscheck=0;
        first_set(x);
         //printf("Bye");
        
    }
    for(int i=0;i<NT_SIZE;i++){
        if(visitedFirst[i]==1)continue;
        gSym x;
        x.isTerminal=false;
        x.nt=i;

       
        //printf("Hi");
        //int epscheck=0;
        follow_set(x);
         //printf("Bye");
        
    }


}
void follow_set(gSym x){
    int check=0;
    for(int i=0;i<MAX_SIZE;i++){
        
        int flag=0;
        for(int j=1;j<Grammar[i].len;j++){
            if(Grammar[i].rule[j].isTerminal==false&&(Grammar[i].rule[j].nt==x.nt)){
                check=1;
                if(j+1==Grammar[i].len){
                    flag=1;
                }
                else {
                    if(Grammar[i].rule[j+1].isTerminal==true){
                        followSet[x.nt].set[followSet[x.nt].size]=Grammar[i].rule[j+1];
                        followSet[x.nt].size++;
                        break;
                    }
                    else{
                        int f=0;
                        for(int k=j+1;k<Grammar[i].len;k++){
                            gSym follow=Grammar[i].rule[k];

                        }
                    
                    

                    

                    }
                }
            }
        }
    }

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
int main()
{
    populate();
    // printf("%s",Terminals[Grammar[MAX_SIZE-1].rule[Grammar[MAX_SIZE-1].len-1].t]);
    //compute_first_set();
    ComputeFirstAndFollowSet();
    int k=0;
    for(int i=0;i<NT_SIZE;i++){
        printf("%i %s ",i,nonTerminals[i]);
        for(int j=0;j<firstSet[i].size;j++){
            printf("%s ",Terminals[firstSet[i].set[j].t]);
            //printf("Yo");
        }
        k++;
        printf("\n");
    }
    //printf("%d",k);

     
    
    
    //printf("%d",firstSet[0].set[0].t);
    //populate();
    //printf("%d",firstSet[0][0].isTerminal);
    //firstSet[0].size++;
    //printf("%d",firstSet[0].size);
}


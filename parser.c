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
int main()
{
    populate();
}


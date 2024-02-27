#define NT_SIZE 
#define T_SIZE 
#define RULE_SIZE 
#define MAX_SIZE 

typedef struct gSym{
    bool term;
    Tokeninfo tinfo; //needs to be imported
    NonTerminal nt; //needs to be changed
}gSym;


gSym Grammar[RULE_SIZE][MAX_SIZE];
gSym firstSet[NT_SIZE][MAX_SIZE];
gSym followSet[NT_SIZE][MAX_SIZE];

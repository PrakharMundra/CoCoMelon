#ifndef parserDef
#define parserDef
#define NT_SIZE 54
#define T_SIZE 61
#define RULE_SIZE 10
#define MAX_SIZE 95
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolTable.h"

typedef enum {TK_ASSIGNOP,TK_COMMENT,TK_FIELDID,TK_ID,TK_NUM,TK_RNUM,TK_FUNID,TK_RUID,TK_WITH,TK_PARAMETERS,TK_END,TK_WHILE,TK_UNION,TK_ENDUNION,TK_DEFINETYPE,TK_AS,TK_TYPE,TK_MAIN,
TK_GLOBAL,TK_PARAMETER,TK_LIST,TK_SQL,TK_SQR,TK_INPUT,TK_OUTPUT,TK_INT,TK_REAL,TK_COMMA,TK_SEM,TK_COLON,TK_DOT,TK_ENDWHILE,TK_OP,TK_CL,TK_IF,TK_THEN,TK_ENDIF,TK_READ,TK_WRITE,TK_RETURN,
TK_PLUS,TK_MINUS,TK_MUL,TK_DIV,TK_CALL,TK_RECORD,TK_ENDRECORD,TK_ELSE,TK_AND,TK_OR,TK_NOT,TK_LT,TK_LE,TK_EQ,TK_GT,TK_GE,TK_NE,TK_DOLLAR,ERROR,TK_DELIM,TK_EPS
} Terminal;

//  char *Terminals[]={"TK_ASSIGNOP","TK_COMMENT","TK_FIELDID","TK_ID","TK_NUM","TK_RNUM","TK_FUNID","TK_RUID","TK_WITH","TK_PARAMETERS","TK_END","TK_WHILE","TK_UNION","TK_ENDUNION","TK_DEFINETYPE","TK_AS","TK_TYPE","TK_MAIN","TK_GLOBAL","TK_PARAMETER","TK_LIST","TK_SQL","TK_SQR","TK_INPUT","TK_OUTPUT","TK_INT","TK_REAL","TK_COMMA","TK_SEM","TK_COLON","TK_DOT","TK_ENDWHILE","TK_OP","TK_CL","TK_IF","TK_THEN","TK_ENDIF","TK_READ","TK_WRITE","TK_RETURN","TK_PLUS","TK_MINUS","TK_MUL","TK_DIV","TK_CALL","TK_RECORD","TK_ENDRECORD","TK_ELSE","TK_AND","TK_OR","TK_NOT","TK_LT","TK_LE","TK_EQ","TK_GT","TK_GE","TK_NE","TK_DOLLAR","ERROR","TK_DELIM","TK_EPS"};


typedef enum { 
program,mainFunction,otherFunctions,function,input_par,output_par,parameter_list,dataType,primitiveDatatype,constructedDatatype,
remaining_list,stmts,typeDefinitions,actualOrRedefined,typeDefinition,fieldDefinitions,fieldDefinition,
fieldtype,moreFields,declarations,declaration,global_or_not,otherStmts,stmt,assignmentStmt,singleOrRecId,
constructedVariable,oneExpansion,moreExpansions,funCallStmt,outputParameters,inputParameters,iterativeStmt,conditionalStmt,
elsePart,ioStmt,arithmeticExpression,expPrime,term,termPrime,factor,highPrecedenceOperator,lowPrecedenceOperators,
booleanExpression,var,logicalOp,relationalOp,returnStmt,optionalReturn,idList,more_ids,definetypestmt,A,option_single_constructed
} NonTerminal;

//  char *nonTerminals[]={"program","mainFunction","otherFunctions","function","input_par","output_par","parameter_list","dataType","primitiveDatatype","constructedDatatype","remaining_list","stmts","typeDefinitions","actualOrRedefined","typeDefinition","fieldDefinitions","fieldDefinition","fieldtype","moreFields","declarations","declaration","global_or_not","otherStmts","stmt","assignmentStmt","singleOrRecId","constructedVariable","oneExpansion","moreExpansions","funCallStmt","outputParameters","inputParameters","iterativeStmt","conditionalStmt","elsePart","ioStmt","arithmeticExpression","expPrime","term","termPrime","factor","highPrecedenceOperator","lowPrecedenceOperators","booleanExpression","var","logicalOp","relationalOp","returnStmt","optionalReturn","idList","more_ids","definetypestmt","A"};

typedef struct gSym{
    bool isTerminal;
    Terminal t; 
    NonTerminal nt;
}gSym;

typedef struct {
    gSym rule[RULE_SIZE];
    int len;
    bool synch;
} Rule;
 typedef struct{
    gSym set[T_SIZE];
    int size;
 } Set;

Rule Grammar[MAX_SIZE];
Set firstSet[NT_SIZE];
Set followSet[NT_SIZE];
int visitedFirst[NT_SIZE];
int visitedFollow[NT_SIZE];
Rule ParseTable[NT_SIZE][T_SIZE-1];
#endif

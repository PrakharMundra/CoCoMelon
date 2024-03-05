/* -----------------------------------------
             Group Number- 25
ID-2021A7PS0576P Name-Nek Manchanda
ID-2021A7PS2429P Name-Utkarsh Sharma
ID-2021A7PS2683P Name-Yash Sejpal
ID-2021A7PS2689P Name-Nishant Singh
ID-2021A7PS2694P Name-Prakhar Mundra
--------------------------------------------- */

#include "parser.h"
#include "variables.h"
#include <time.h>
extern stack *s;
extern FILE *poi;
extern parseTree *root;
int main(int argc, char *argv[])
{

  int choice;

  printf("\033[1;32m\n\n\t\t --- CS-F363 Compiler Construction Project Group 25 --- \n\n\033[0m");
  printf("\033[1;35m \t----------\n\033[0m");
  printf("\033[1;35m > FIRST and FOLLOW set automated\n\033[0m");
  printf("\033[1;35m > Both Lexical and Syntax Analysis module implemented\n\033[0m");
  printf("\033[1;35m > Parse Tree generated and printed\n\033[0m");
  printf("\033[1;35m > Synch Set Implemented\n\033[0m");
  printf("\033[1;35m \t----------\n\033[0m");
  while (1)
  {
    root = createTree();
    lexer_init();
    s = (stack *)malloc(sizeof(stack));
    create_stack();

    printf("\033[1;36m \n 0. Exit\033[0m");
    printf("\033[1;36m \n 1. Remove Comments\033[0m");
    printf("\033[1;36m \n 2. Lexical Analysis\033[0m");
    printf("\033[1;36m \n 3. Syntactic Analysis\033[0m");
    printf("\033[1;36m \n 4. Print time taken\033[0m");
    printf("\033[1;36m \n Enter your choice : \033[0m");
    scanf("%d", &choice);
    switch (choice)
    {
    case 0:
      printf("\033[1;31m\n------------------------\n\033[0m");
      printf("\033[1;31m \tExiting\n\033[0m");
      printf("\033[1;31m------------------------\n\033[0m");
      exit(0);
      break;
    case 1:;
      removeComments(argv[1], "cleanfile.txt");
      printf("\033[1;32m\n >> Cleanfile.txt created with comments removed\n\033[0m");
      break;
    case 2:;
      lexer_init();
      printTokens(argv[1]);
      printf("\033[1;32m\n >> All tokens and corresponding lexeme values displayed along with Lexical errors, if any\n\033[0m");
      break;

    case 3:;
      poi = fopen(argv[2], "w");
      fclose(poi);
      poi = fopen(argv[2], "a");
      populate();
      ComputeFirstAndFollowSet();
      createParseTable();
      generateParseTree(argv[1]);
      fclose(poi);
      break;

    case 4:;
      poi = fopen(argv[2], "w");
      fclose(poi);
      poi = fopen(argv[2], "a");
      clock_t start_time, end_time;
      double total_CPU_time, total_CPU_time_in_seconds;
      start_time = clock();
      populate();
      ComputeFirstAndFollowSet();
      createParseTable();
      generateParseTree(argv[1]);
      end_time = clock();
      total_CPU_time = (double)(end_time - start_time);
      total_CPU_time_in_seconds = total_CPU_time / CLOCKS_PER_SEC;
      printf("\033[1;32m\n\n------------------------------------------------------------------------\n\033[0m");
      printf("\033[1;32m\t> Total CPU time: %5f \n \t> Total CPU time in seconds: %5f \033[0m", total_CPU_time, total_CPU_time_in_seconds);
      printf("\033[1;32m\n------------------------------------------------------------------------\n\033[0m");
      fclose(poi);
      // Print both total_CPU_time and total_CPU_time_in_seconds
      break;
    }
  }
  free(root);
  free(s);
}
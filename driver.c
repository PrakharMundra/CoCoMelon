#include "parser.h"
#include <time.h>
int main(int argc, char *argv[])
{
    int choice;
    printf("\033[1;35m FIRST and FOLLOW set automated\n\033[0m");
    printf("\033[1;35m Both Lexical and Syntax Analysis module implemented\n\033[0m");
    printf("\033[1;35m Parse Tree generated and printed\n\033[0m");
    printf("\033[1;35m Synch Set Implemented\n\033[0m");
    printf("\033[1;35m \t----------\n\033[0m");
    while (1)
    {
        printf("\033[1;36m \n 0.Exit\033[0m");
        printf("\033[1;36m \n 1.Remove Comments\033[0m");
        printf("\033[1;36m \n 2.Lexical Analysis\033[0m");
        printf("\033[1;36m \n 3.Syntactic Analysis\033[0m");
        printf("\033[1;36m \n 4.Print time taken\033[0m");
        printf("\033[1;36m \n Enter your choice\n\033[0m");
        scanf("%d", &choice);
        switch (choice)
        {
        case 0:
            printf("\033[1;31m \tExiting\n\033[0m");
            printf("\t----------------------------------\n");
            exit(0);
            break;
        case 1:;
            removeComments(argv[1], "cleanfile.txt");
            printf("\033[1;32m Cleanfile.txt created with comments removed\n\033[0m");
            break;
        case 2:;
            lexer_init();
            printTokens(argv[1]);
            break;

        case 3:;
            poi = fopen(argv[2], "a");
            populate();
            ComputeFirstAndFollowSet();
            createParseTable();
            generateParseTree(argv[1]);
            inorderTraversal(root);
            fclose(poi);
            break;
        case 4:;
            clock_t start_time, end_time;
            unsigned total_CPU_time, total_CPU_time_in_seconds;
            start_time = clock();
            // invoke your lexer and parser here
            populate();
            ComputeFirstAndFollowSet();
            createParseTable();
            generateParseTree(argv[1]);
            end_time = clock();
            // printf("%ld    %ld\n",start_time,end_time);
            total_CPU_time = (double) (end_time - start_time)/((double)CLOCKS_PER_SEC/1000);
            printf("%f",total_CPU_time);
            total_CPU_time_in_seconds = ((double)total_CPU_time)/((double)CLOCKS_PER_SEC);
            printf("\033[1;31m Total CPU time: %5f \nTotal CPU time in seconds: %5f \033[0m",total_CPU_time,total_CPU_time_in_seconds);
            // Print both total_CPU_time and total_CPU_time_in_seconds
        }
    }
}
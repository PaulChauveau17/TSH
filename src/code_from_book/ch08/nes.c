#include <stdio.h>

    int foo(char *);

    int main(int argc, char *argv[])
    {
            unsigned char buffer[520]="";
            if(argc !=2)
                    return printf("Please supply an argument!\n");
            foo(argv[1]);
            return 0;
     }

     int foo(char *input)
     {
            unsigned char buffer[600]="";
            printf("%.8X\n",&buffer);
            strcpy(buffer,input);
            return 0;
     }

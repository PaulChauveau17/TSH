/* Vulnerable Program (vuln.c)*/
 
#include <windows.h>
#include <stdio.h>

#define USERMAXSIZE     32
#define USERMAXLEN     16

int check_username(char *username)
{
     char buffer[USERMAXLEN];

     lstrcpynA(buffer, username, USERMAXSIZE-1);

     /*
          Other function code to examine username
          ...
     */

     return(0);
}

int main(int argc, char **argv)
{
     if(argc != 2)
     {
          fprintf(stderr, "Usage: %s <buffer>\n", argv[0]);
          exit(-1);
     }
     while(1)
     {
          check_username(argv[1]);
          Sleep(1000);
     }
     return(0);
}

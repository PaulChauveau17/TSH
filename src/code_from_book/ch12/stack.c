// stack.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[] )
{
        char buff[ 16 ];

        printf("buff: 0x%08x\n", buff );

        if( argc <= 1 )
                return printf("Error - param expected\n");

        strcpy( (char *)buff, argv[1] );

        return 0;
}

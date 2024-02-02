#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned *malloc_zones;

int main( int argc, char *argv[] )
{
        char *p1 = NULL;
        char *p2 = NULL;

        printf("malloc_zones: %08x\n", *malloc_zones );
        printf("p1: %08x\n", p1 );

        p1 = malloc( 0x10 );

        while( p2 < *malloc_zones )
                p2 = malloc( 0x5000 );

        printf("p2: %08x\n", p2 );

        unsigned *pu = p1;

        while( pu < (*malloc_zones + 0x20) )
                *pu++ = 0x41414141;

        free( p1 );
        free( p2 );

        return 0;
}

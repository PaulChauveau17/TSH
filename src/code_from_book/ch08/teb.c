#include <stdio.h>

     int main()
     {
             __asm{
                    mov eax, dword ptr fs:[0x18]
                    push eax
                    }
            printf("TEB: %.8X\n");
     
            __asm{
                    add esp,4
                    }

            return 0;
     }

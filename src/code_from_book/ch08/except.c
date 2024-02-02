#include <stdio.h>
#include <windows.h>

DWORD MyExceptionHandler(void)
{
             printf("In exception handler....");
             ExitProcess(1);
             return 0;
}

int main()
{
              __try
              {
                   __asm
{
     // Cause an exception
                            xor eax,eax
                            call eax
}

            }
            __except(MyExceptionHandler())
            {
                    printf("oops...");
             }
             return 0;
}

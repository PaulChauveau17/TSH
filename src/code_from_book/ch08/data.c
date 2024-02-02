#include <stdio.h>
#include <windows.h>

unsigned char buffer[32]="";
FARPROC mprintf = 0;
FARPROC mstrcpy = 0;

int main(int argc, char *argv[])
{    
     HMODULE l = 0;
     l = LoadLibrary("msvcrt.dll");
     if(!l)
            return 0;
     mprintf = GetProcAddress(l,"printf");
     if(!mprintf)
            return 0;
     mstrcpy = GetProcAddress(l,"strcpy");
     if(!mstrcpy)
            return 0;
     (mstrcpy)(buffer,argv[1]);
     __asm{ add esp,8 }
     (mprintf)("%s",buffer);
     __asm{ add esp,8 }
     FreeLibrary(l);

     return 0;
}

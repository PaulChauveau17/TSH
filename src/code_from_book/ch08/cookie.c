#include <stdio.h>
#include <windows.h>

int main()
{
            FILETIME ft;
            unsigned int Cookie=0;
            unsigned int tmp=0;
            unsigned int *ptr=0;
            LARGE_INTEGER perfcount;

            GetSystemTimeAsFileTime(&ft);
            Cookie = ft.dwHighDateTime ^ ft.dwLowDateTime;
            Cookie = Cookie ^ GetCurrentProcessId();
            Cookie = Cookie ^ GetCurrentThreadId();
            Cookie = Cookie ^ GetTickCount();
            QueryPerformanceCounter(&perfcount);
            ptr = (unsigned int)&perfcount;
            tmp = *(ptr+1) ^ *ptr;
            Cookie = Cookie ^ tmp;
            printf("Cookie: %.8X\n",Cookie);
            return 0;
}

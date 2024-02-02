#include <stdio.h>
#include <windows.h>

     HANDLE hp=NULL;
     int ReturnHostFromUrl(char **, char *);

     int main()
     {
            char *ptr = NULL;
            hp = HeapCreate(0,0x1000,0x10000);
            ReturnHostFromUrl(&ptr,"http://www.ngssoftware.com/index.html");
            printf("Host is %s",ptr);
            HeapFree(hp,0,ptr);
            return 0;

     }

     int ReturnHostFromUrl(char **buf, char *url)
     {
            int count = 0;
            char *p = NULL;
            char buffer[40]="";

            // Get a pointer to the start of the host
            p = strstr(url,"http://");
            if(!p)
                    return 0;
            p = p + 7;
            // do processing on a local copy
            strcpy(buffer,p); // <------ NOTE 1
            // find the first slash
            while(buffer[count] !='/')
                    count ++;
            // set it to NULL
            buffer[count] = 0;
            // We now have in buffer the host name
            // Make a copy of this on the heap
            p = (char *)HeapAlloc(hp,0,strlen(buffer)+1);
            if(!p)
                    return 0;
            strcpy(p,buffer);
            *buf = p; // <-------------- NOTE 2
            return 0;
     }

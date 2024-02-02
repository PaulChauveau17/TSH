  #include <stdio.h>
  #include <stdlib.h>

  int main()
  {
          asm("\
                  xor %eax, %eax;\
                  xor %ecx, %ecx;\
                  xor %edx, %edx;\
                  mov $0x01, %al;\
                  xor %ebx, %ebx;\
                  mov $0x02, %bl;\
                  int $0x80;\
                  ");

          return 1;
  }

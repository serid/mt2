; Integer is passed in eax
; Buffer is passed in edi
itoa:
    push ebp
    mov ebp,esp

    mov ebx,edi ; save original edi (needed to reverse later)
convert_itoa:
    test eax, eax
    je done_loop_itoa

    ; shift number right and extract one digit
    mov edx, 0
    mov eax, eax
    mov ecx, 10
    idiv ecx
    ; eax ; quotient
    add edx, 48 ; convert digit to character
    mov [edi], edx ; store character
    inc edi
    jmp convert_itoa

done_loop_itoa:
    ; reverse output now
    ; ebx iterates from offset 0 forward
    ; edi iterates from past-last element backward
    dec edi
reverse_loop_itoa:
    ; swap chars
    mov ch,[edi] ; ecx is tmp
    xchg ch,[ebx]
    mov [edi],ch
    inc ebx
    dec edi
    
    cmp ebx, edi
    jl reverse_loop_itoa

    mov esp,ebp
    pop ebp
    ret

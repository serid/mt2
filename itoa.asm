; Integer is passed in eax
; Buffer is passed in edi
; Returns output number length in eax
itoa:
    push ebp
    mov ebp,esp

    mov ebx,edi ; save original edi (needed to reverse later)
    
    ; if number is 0 then shortcut
    cmp eax, 0
    jnz convert_itoa
    mov [edi], byte '0'
    mov [edi+1], byte 0xA
    mov eax, 2 ; output number length
    jmp end_

convert_itoa:
    test eax, eax
    je done_loop_itoa

    ; shift number right and extract one digit
    mov edx, 0
    mov eax, eax
    mov ecx, 10
    idiv ecx
    ; eax ; quotient
    ; Now 0 <= edx <= 9
    add dl, 48 ; convert digit to character
    
    mov ecx, eax ; store eax
    mov al, dl
    stosb ; write char to output
    mov eax, ecx ; restore eax

    jmp convert_itoa

done_loop_itoa:
    ; save output number length in eax
    mov eax, edi
    sub eax, ebx

    ; append a newline
    add eax, 1
    mov [edi], byte 0xA

    ; reverse output now
    ; ebx iterates from offset 0 forward
    ; edi iterates from past-last element backward
    dec edi
reverse_loop_itoa:
    ; swap chars
    mov cl, [edi] ; ecx is tmp
    xchg cl, [ebx]
    mov [edi], cl
    inc ebx
    dec edi
    
    cmp ebx, edi
    jl reverse_loop_itoa

end_:

    mov esp,ebp
    pop ebp
    ret

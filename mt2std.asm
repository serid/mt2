funcadd:
add esi, edi
ret

funcsub:
sub esi, edi
ret

funcnot:
mov eax, 0
test esi, esi
sete al
mov esi, eax
ret

funceq: ; esi = (esi == edi)
mov eax, 0
cmp esi, edi
sete al
mov esi, eax
ret

funcneq: ; esi = (esi != edi)
mov eax, 0
cmp esi, edi
setne al
mov esi, eax
ret

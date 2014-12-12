.section data

str: .ascii "Hello World!\n"
	strlen = . - str

num: .long 1337

.section text

.global _start

_start:
    movl $4, %eax
    movl $1, %ebx
    movl $str, %ecx
    movl $strlen, %edx
    int $0x80

    movl $1, %eax
    movl $0, %ebx
    int $0x80



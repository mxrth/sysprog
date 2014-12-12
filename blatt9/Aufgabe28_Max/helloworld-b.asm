.macro write fd, buf, len
    movl $4, %eax
    movl \fd, %ebx
    movl \buf, %ecx
    movl \len, %edx
    int $0x80
.endm

/*data section*/
.section .data
/* the string we want to output */
str: .ascii "\nHello World!\n" 
	strlen = . - str 
	/*from the docs: The special symbol `.' refers to the current address 
	  that as is assembling into
	  so strlen simply is the current adddres (directly after `string:` minus the start of string
	  and thus the length of "Hello World!\n"
	*/
str_buf_rev: .space 30 /*we assume that a number has no more than 30 bytes in length*/
str_len: .long 0
str_buf: .space 30

num: .long 31337 /*store a number*/

.section .text /*now we hit the .text section, where all code lives*/

.global _start /*the entry point, made global for linker visibility*/

_start: /*finyally, let the fun begin!*/
   
    write_reversed:
	movl (num), %eax /*move number into eax (we support longs, so 32 bits are needed*/
	cdq		    /*sign extend that number, so eax is now in EDX:EAX*/
	movl $10 ,%ebx
	div %ebx /*remainder is now in %edx, quotient in %eax*/
	
	movl %eax, (num) /*update num*/

	addl $48, %edx
	movl $str_buf_rev, %ecx
	addl (str_len), %ecx
	movb %dl, (%ecx)

	incl (str_len)
	test %eax, %eax
	jnz write_reversed

    movl $str_buf_rev, %eax
    addl (str_len), %eax
    movl (str_len), %ecx
    movl $str_buf, %ebx
    reverse:
	decl %eax
	movl (%eax), %edx
	movl %edx,(%ebx) 
	incl %ebx
	loop reverse


    write $1, $str_buf, (str_len)
    /*call write(stdout, str, strlen)*/
    write $1, $str, $strlen

       /*call exit(0) */
    movl $1, %eax /*exit has syscall-number 1*/
    movl $0, %ebx /*exit with statuscode 0*/
    int $0x80

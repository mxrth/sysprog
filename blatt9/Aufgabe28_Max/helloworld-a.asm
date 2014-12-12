/*data section*/
.section .data
/* the string we want to output */
str: .ascii "Hello World!\n" 
	strlen = . - str 
	/*from the docs: The special symbol `.' refers to the current address 
	  that as is assembling into
	  so strlen simply is the current adddres (directly after `string:` minus the start of string
	  and thus the length of "Hello World!\n"
	*/

num: .long 1337 /*store a number*/

.section .text /*now we hit the .text section, where all code lives*/

.global _start /*the entry point, made global for linker visibility*/

_start: /*finyally, let the fun begin!*/
    /*call write(stdout, str, strlen)*/
    movl $4, %eax /*write has syscall number 4*/
    movl $1, %ebx /* write to stdout, fd 1 */
    movl $str, %ecx /* pointer to str */
    movl $strlen, %edx /*strlen*/
    int $0x80 /*do the actual syscall*/

    /*call exit(0) */
    movl $1, %eax /*exit has syscall-number 1*/
    movl $0, %ebx /*exit with statuscode 0*/
    int $0x80



.section .data

str:	.ascii "Hello world!\n"
		strlen = . - str

num: 	.long 1337

.section .text

/*This label is for the linker*/
.global _start

_start:
	
	/*System call to the function 'write'*/
	movl $4, %eax		/*Number of the system call, here (sys_write)*/
	movl $1, %ebx		/*File descriptor of stdout*/
	movl $str, %ecx		/*String to write*/
	movl $strlen, %edx	/*String length*/
	int $0x80			/*Call the kernel*/

	/*System call to the function exit*/
	movl $1, %eax		/*Number of the system call, here (sys_exit)*/
	movl $0, %ebx		/*First parameter for sys_exit*/
	int $0x80			/*Call the kernel*/

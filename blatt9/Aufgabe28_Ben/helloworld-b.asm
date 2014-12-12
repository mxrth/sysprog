.macro write fd, buf, length
	movl $4, %eax		/*Number of the system call, here (sys_write)*/
	movl \fd, %ebx		/*File descriptor of stdout*/
	movl \buf, %ecx		/*String to write*/
	movl \length, %edx 		/*String length*/
	int $0x80			/*Call the kernel*/
.endm

/*Here the data section of the program begins*/
.section .data

str:	.ascii "Hello world!\n"
		strlen = . - str

/*This will be used as a buffer for the string which contains the number that has to be printed*/
strbuf: .space 30

num: 	.long 1337

.section .text

/*This label is for the linker*/
.global _start

_start:
	
	/*System call to the function 'write'*/
	write $1, $str, $strlen

	/*Here the program converts the number num in */
	convert_start:
		movl (num), %eax	/*Move the value stored in num to eax, this number will be divided (also called the 'dividend')*/
		cdq					/*Extends eax into edx, this is needed to use the division-function*/

		movl $10, %ebx		/*This is the number by which we will divide, this is later the argument for div*/
		div %ebx
		/*The remainder, the number in which we are interested, is now stored in edx*/

		addl $48, %edx

		movb %dl, (strbuf)

	/*System call to the function 'write'*/
	write $1, $strbuf, $1

	/*System call to the function exit*/
	movl $1, %eax		/*Number of the system call, here (sys_exit)*/
	movl $0, %ebx		/*First parameter for sys_exit*/
	int $0x80			/*Call the kernel*/

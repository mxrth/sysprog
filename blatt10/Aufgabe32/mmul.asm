#32-Bit ,following the cdecl calling convention

#PURPOSE: Multipilies two matrices and saves result in new matrix
#INPUT: int n - number of rows of Matrix M1
#		int m - number of columns of Matrix M1 and rows of Matrix M2
#		int k - number of columns of Matrix M2
#OUTPUT: void
#NOTES: Matrix have to be aligned. No test included
#Variables:	int x - counter for cols of M2 -saved on the stack at -4(%ebs)
#		int y - counter for rows of M1 -saved on the stack at -8(%ebs)
#		int z - counter for cols of M1/ rows of M2 - in register %edx

		
.section .text
.globl mmul
.type mmul,@function

mmul:
		push %ebp			# saving current basepointer	
		movl %esp, %ebp 		# copy stackpointer to %ebp
		subl $16, %esp			# make room for four local variables: x,y,z and temp
		movl $0, %eax			# y = 0
		movl %eax, -4(%ebp)		# save y on the stack
y_loop: 	movl -4(%ebp), %eax		# get y from stack into %eax
		movl 8(%ebp), %ecx 		# get n from stack and put into %ecx
		cmpl %eax, %ecx 		# compare y and n
		je finish			# if y==n jump to finish
		movl %eax, -4(%ebp)		# save y on the stack
		movl $0, %eax			# x = 0
		movl %eax, -8(%ebp)		# save x on the stack
x_loop: movl 	-8(%ebp), %eax			# put x into %eax
		movl 16(%ebp), %ecx  		# put k into %ecx
		cmpl %eax, %ecx 		# cmp x to k
		je inc_y			# if equal jump to inc_y
		movl $0, %eax			# z = 0
		movl %eax, -12(%ebp)		# save z to stack
		movl $0, %eax			# temp = 0
		movl %eax, -16(%ebp)		# save temp to stack
z_loop: movl 	12(%ebp), %ecx			# %ecx = m
		movl -12(%ebp), %eax		# %eax = z
		cmpl %eax, %ecx 		# compare z to m
		je result			# if equal jump to result
		movl -4(%ebp), %edx		# %edx = y
		imul %edx, %ecx			# %ecx = y*m
		addl %eax, %ecx			# %ecx = y*m + z
		imul $4, %ecx			# %ecx = 4* y*m + z
		movl 20(%ebp), %eax		# %eax = *M1
		addl %eax, %ecx			# %ecx = 4 *y*m + z + *M1
		movl (%ecx), %edx		# get value from memoryadress in %ecx put it in %edx
		movl 16(%ebp), %ecx		# %ecx = k
		movl -12(%ebp), %eax		# %eax = z
		imul %eax, %ecx			# %ecx = z*k
		movl -8(%ebp), %eax		# %eax = x
		addl %eax, %ecx			# %ecx = z*k +x
		imul $4, %ecx			# %ecx = 4* z*k+x
		movl 24(%ebp), %eax		# %eax = *M2
		addl %eax, %ecx			# %ecx = 4 *z*k +x + *M2
		movl (%ecx), %eax		# get value from memoryadress in %ecx and put it in %eax
		imul %eax, %edx			# multiply %edx and %eax and put it in %edx
		movl -16(%ebp), %eax		# put temp into %eax
		addl %edx, %eax			# add %edx to %eax
		movl %eax, -16(%ebp)		# save %eax to temp
		movl -12(%ebp), %eax		# put z into %eax
		incl %eax			# z++
		movl %eax, -12(%ebp)		# save z to stack
		jmp z_loop 			# unconditional jump to z_loop
result: movl 16(%ebp), %eax			# %eax = k
		movl -4(%ebp), %ecx		# %ecx = y
		imul %eax, %ecx			# %ecx = k*y
		movl -8(%ebp), %eax		# %eax = x
		addl %eax, %ecx			# %ecx = k*y + x
		imul $4, %ecx			# %ecx = 4 * k*y + x
		movl 28(%ebp), %edx		# %edx = *M
		addl %edx, %ecx			# %ecx = 4*k*y + x + *M
		movl -16(%ebp), %edx		# get temp and put it in %edx
		movl %edx, (%ecx)		# save temp to adress in %ecx
		incl %eax			# inc x in %eax
		movl %eax, -8(%ebp)		# save x on the stack
		jmp x_loop			# unconditional jump to x_loop
inc_y: 		movl -4(%ebp), %eax		# put y into %eax
		incl %eax			# y++ 
		movl %eax, -4(%ebp)		# save y to stack
		jmp	y_loop			# unconditional jump to y_loop
finish: movl %ebp,%esp			# restore stackpointer
		popl %ebp			# remove old basepointer adress
		ret

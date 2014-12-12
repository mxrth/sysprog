all: hello

hello.o: helloworld-b.asm
	as -g --gstabs -o hello.o  helloworld-b.asm
hello: hello.o
	ld -o hello hello.o


clean:
	-rm hello.o hello

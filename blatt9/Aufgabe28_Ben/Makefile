all: helloworld-a helloworld-b

OBJECTS := helloworld-a.o helloworld-b.o

EXECUTABLES := helloworld-a helloworld-b

helloworld-a.o: helloworld-a.asm
	as -gstabs -o $@ $^

helloworld-b.o: helloworld-b.asm
	as -gestabs -o $@ $^

helloworld-a: helloworld-a.o
	ld -o $@ $^

helloworld-b: helloworld-b.o
	ld -o $@ $^

.PHONY: clean

clean:
	-rm $(OBJECTS) $(EXECUTABLES)
all: helloworld

OBJECTS := helloworld-a.o

EXECUTABLES := helloworld

helloworld-a.o: helloworld-a.asm
	as -gstabs -o $@ $^

helloworld: helloworld-a.o
	ld -o $@ $^

.PHONY: clean

clean:
	-rm $(OBJECTS) $(EXECUTABLES)
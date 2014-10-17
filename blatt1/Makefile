CFLAGS = -Wall -Wextra --std=c99 --pedantic

CC = clang

OBJECTS = main.o input.o output.o list.o mystring.o 


person_list: input.o output.o main.o output.o list.o mystring.o
	$(CC) $(CFLAGS) -o person_list $(OBJECTS)

#These can be made with implicit rules, only the dependencies are specified

main.o: input.h mystring.h list.h 

input.o: input.h mystring.h list.h

output.o: list.h

list.o: list.h

mystring.o: mystring.h

.PHONY: clean
clean:
	-rm -f $(OBJECTS)

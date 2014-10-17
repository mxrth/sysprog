CFLAGS = -Wall -Wextra --std=c99 --pedantic

CC = clang

OBJECTS = main.o input.o output.o list.o mystring.o 

EXECUTABLE = person_list

$(EXECUTABLE): input.o output.o main.o output.o list.o mystring.o
	$(CC) $(CFLAGS) -o person_list $(OBJECTS)

#These can be made with implicit rules, only the dependencies are specified

main.o: main.c input.h list.h 

input.o: input.c input.h mystring.h list.h

output.o: output.c list.h

list.o: list.c list.h

mystring.o: mystring.c mystring.h

.PHONY: clean
clean:
	-rm -f $(OBJECTS) $(EXECUTABLE)

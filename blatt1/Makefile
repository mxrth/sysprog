CFLAGS = -Wall -Wextra --std=c99 --pedantic -g3  

CC = clang

OBJECTS = main.o input.o output.o list.o mystring.o 

EXECUTABLE = person_list

CLANG_SANITIZE_FLAGS = -fsanitize=address,integer,undefined

ifdef SANITIZE
CFLAGS += $(CLANG_SANITIZE_FLAGS) -O3
endif

ifeq ($(CC), clang)
#More warnings!
CFLAGS += -Weverything
endif

$(EXECUTABLE): input.o output.o main.o output.o list.o mystring.o
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS)

#These can be made with implicit rules, only the dependencies are specified

main.o: main.c input.h list.h 

input.o: input.c input.h mystring.h list.h

output.o: output.c list.h

list.o: list.c list.h

mystring.o: mystring.c mystring.h

.PHONY: clean
clean:
	-rm -f $(OBJECTS) $(EXECUTABLE)

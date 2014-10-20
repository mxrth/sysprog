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

$(EXECUTABLE): 
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS)

#These can be made with implicit rules, only the dependencies are specified

main.o: main.c input.h list.h 



.PHONY: clean
clean:
	-rm -f $(OBJECTS) $(EXECUTABLE)

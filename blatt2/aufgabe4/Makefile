CFLAGS = -Wall -Wextra --std=c99 --pedantic -g3  

CC = gcc

OBJECTS = springerproblem.o brett.o 

EXECUTABLE = springer

CLANG_SANITIZE_FLAGS = -fsanitize=address,integer,undefined

ifdef SANITIZE
CFLAGS += $(CLANG_SANITIZE_FLAGS) -O3
endif

ifeq ($(CC), clang)
#More warnings!
CFLAGS += -Weverything
endif

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS)

#These can be made with implicit rules, only the dependencies are specified

springerproblem.o: springerproblem.c brett.h output.h

brett.o : brett.c brett.h

.PHONY: clean
clean:
	-rm -f $(OBJECTS) $(EXECUTABLE)

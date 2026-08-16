# ----------------------------------------------------------------------- #
#  Makefile																  #
# ----------------------------------------------------------------------- #

SOURCES = main.c engine.c board.c
OBJECTS = $(SOURCES:.c=.o)
TARGETS = test main

all: $(TARGETS)

# removes all program files
clean:
	rm -f $(TARGETS)

# removes all .o files AND program files
clobber: clean
	rm -f *.o

# make the program
main: main.o engine.o board.o parameters.o move.o mask.o square.o color.o
	gcc $^ -o $@

test: test.o parameters.o square.o color.o
	gcc $^ -o $@

# .o file creations
main.o: main.c engine.h
	gcc -c $< -o $@
engine.o: engine.c 
	gcc -c $< -o $@
board.o: board.c mask.h
	gcc -c $< -o $@

test.o: test.c parameters.h
	gcc -c $< -o $@
parameters.o: parameters.c square.h helpers.h
	gcc -c $< -o $@
square.o: square.c helpers.h
	gcc -c $< -o $@
color.o: color.c
	gcc -c $< -o $@


#.NUMBER = 2290
#diff:
#	./fibc $(.NUMBER) >| file1
#	./fiboo $(.NUMBER) >| file2
#	-diff file1 file2 >| checkFile.txt
# ----------------------------------------------------------------------- #
#  Makefile																  #
# ----------------------------------------------------------------------- #

GTK_CFLAGS = $(shell pkg-config --cflags gtk4)
GTK_LIBS   = $(shell pkg-config --libs gtk4)
CFLAGS = -std=c23 -Wall -Wextra -Wpedantic -Wshadow -I include -fsanitize=address -g -O0 $(GTK_CFLAGS)

SOURCES = $(wildcard src/*.c)
OBJECTS = $(patsubst src/%.c, obj/%.o, $(SOURCES))
PROGRAMS = bin/test bin/position bin/termGame bin/guiGame

# make both executables
all: $(PROGRAMS)

# removes all program files
clean:
	rm -f $(PROGRAMS)
# removes all files from the bin and object directories
clobber: clean
	rm -rf obj bin
# remakes all files
re: clobber all

# make the programs
bin/test: obj/test.o $(OBJECTS) | bin
	gcc $(CFLAGS) $(GTK_LIBS) -o $@ $^
bin/position: obj/position.o $(OBJECTS) | bin
	gcc $(CFLAGS) $(GTK_LIBS) -o $@ $^
bin/termGame: obj/termGame.o $(OBJECTS) | bin
	gcc $(CFLAGS) $(GTK_LIBS) -o $@ $^
bin/guiGame: obj/guiGame.o $(OBJECTS) | bin
	gcc $(CFLAGS) $(GTK_LIBS) -o $@ $^

# .o file creations
obj/termGame.o: exe/termGame.c |obj
	gcc $(CFLAGS) -c $< -o $@
obj/gui.o: src/gui.c |obj
	gcc $(CFLAGS) -c $< -o $@
obj/%.o: exe/%.c | obj
	gcc $(CFLAGS) -c $< -o $@
obj/%.o: src/%.c | obj
	gcc $(CFLAGS) -c $< -o $@

# create directories
obj bin:
	mkdir -p $@

-include $(wildcard obj/*.d)

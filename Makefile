# ----------------------------------------------------------------------- #
#  Makefile																  #
# ----------------------------------------------------------------------- #

SOURCES = $(wildcard src/*.c)
OBJECTS = $(patsubst src/%.c, obj/%.o, $(SOURCES))

TEST_OBJS = obj/test.o $(OBJECTS)
MAIN_OBJS = obj/main.o $(OBJECTS)
GAME_OBJS = obj/game.o $(OBJECTS)
PSTN_OBJS = obj/position.o $(OBJECTS)

GTK_CFLAGS = $(shell pkg-config --cflags gtk4)
GTK_LIBS   = $(shell pkg-config --libs gtk4)
CFLAGS = -std=c23 -Wall -Wextra -Wpedantic -Wshadow -I include -fsanitize=address -g -O0

PROGRAMS = bin/test bin/main bin/game bin/position

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
bin/test: $(TEST_OBJS) | bin
	gcc $(CFLAGS) -o $@ $^ $(GTK_LIBS)
bin/main: $(MAIN_OBJS) | bin
	gcc $(CFLAGS) -o $@ $^ $(GTK_LIBS)
bin/game: $(GAME_OBJS) | bin
	gcc $(CFLAGS) -o $@ $^ $(GTK_LIBS)
bin/position: $(PSTN_OBJS) | bin
	gcc $(CFLAGS) -o $@ $^ $(GTK_LIBS)

# .o file creations
obj/userint.o: src/userint.c | obj
	gcc $(CFLAGS) $(GTK_CFLAGS) -c $< -o $@
obj/test.o: exe/test.c | obj
	gcc $(CFLAGS) $(GTK_CFLAGS) -c $< -o $@
obj/%.o: exe/%.c | obj
	gcc $(CFLAGS) -c $< -o $@
obj/%.o: src/%.c | obj
	gcc $(CFLAGS) -c $< -o $@

# create directories
obj bin:
	mkdir -p $@

-include $(wildcard obj/*.d)

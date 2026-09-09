# ----------------------------------------------------------------------- #
#  Makefile																  #
# ----------------------------------------------------------------------- #

SOURCES = $(wildcard src/*.c)
OBJECTS = $(patsubst src/%.c, obj/%.o, $(SOURCES))

TEST_OBJS = obj/test.o $(OBJECTS)
MAIN_OBJS = obj/main.o $(OBJECTS)
GAME_OBJS = obj/game.o $(OBJECTS)

CFLAGS = -Wall -Wextra -Wpedantic -Wshadow -I include

# make both executables
all: bin/test bin/main bin/game

# removes all program files
clean:
	rm -f bin/test bin/main
# removes all files from the bin and object directories
clobber: clean
	rm -rf obj bin
# remakes all files
re: clobber all

# make the programs
bin/test: $(TEST_OBJS) | bin
	gcc $(CFLAGS) -o $@ $^
bin/main: $(MAIN_OBJS) | bin
	gcc $(CFLAGS) -o $@ $^
bin/game: $(GAME_OBJS) | bin
	gcc $(CFLAGS) -o $@ $^

# .o file creations
obj/main.o: exe/main.c | obj
	gcc $(CFLAGS) -c $< -o $@
obj/test.o: exe/test.c | obj
	gcc $(CFLAGS) -c $< -o $@
obj/game.o: exe/game.c | obj
	gcc $(CFLAGS) -c $< -o $@
obj/%.o: src/%.c | obj
	gcc $(CFLAGS) -c $< -o $@

# create directories
obj bin:
	mkdir -p $@

	
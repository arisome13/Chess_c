# ----------------------------------------------------------------------- #
#  Makefile																  #
# ----------------------------------------------------------------------- #

SOURCES = $(wildcard src/*.c)
OBJECTS = $(patsubst src/%.c, obj/%.o, $(SOURCES))

TEST_OBJS = obj/test.o $(OBJECTS)
MAIN_OBJS = obj/main.o $(OBJECTS)
GAME_OBJS = obj/game.o $(OBJECTS)
PSTN_OBJS = obj/position.o $(OBJECTS)

CFLAGS = -std=c23 -Wall -Wextra -Wpedantic -Wshadow -I include

# make both executables
all: bin/test bin/main bin/game bin/position

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
bin/position: $(PSTN_OBJS) | bin
	gcc $(CFLAGS) -o $@ $^

# .o file creations
obj/%.o: exe/%.c | obj
	gcc $(CFLAGS) -c $< -o $@
obj/%.o: src/%.c | obj
	gcc $(CFLAGS) -c $< -o $@

# create directories
obj bin:
	mkdir -p $@

	
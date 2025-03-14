EXE = anthill
CFLAGS = -g -Wall -c -ansi -pedantic

.PHONY = all clean clear check

all: anthill

anthill: command.o game_actions.o game_loop.o game.o game_reader.o graphic_engine.o space.o object.o player.o set.o character.o
	gcc -o $(EXE) $^ -L. -lscreen
	
command.o: command.c command.h types.h
	gcc $(CFLAGS) $<

game_actions.o: game_actions.c game_actions.h command.h types.h game.h space.h object.h player.h game_reader.h
	gcc $(CFLAGS) $<

game_loop.o: game_loop.c command.h types.h game.h space.h object.h player.h game_actions.h game_reader.h graphic_engine.h
	gcc $(CFLAGS) $<

game.o: game.c game.h command.h types.h space.h object.h player.h game_reader.h
	gcc $(CFLAGS) $<
	
game_reader.o: game_reader.c game_reader.h types.h game.h command.h space.h object.h player.h
	gcc $(CFLAGS) $<

graphic_engine.o: graphic_engine.c graphic_engine.h game.h command.h types.h space.h object.h player.h set.h game_reader.h libscreen.h
	gcc $(CFLAGS) $<

space.o: space.c space.h types.h object.h set.h
	gcc $(CFLAGS) $<

object.o: object.c object.h types.h
	gcc $(CFLAGS) $<

player.o: player.c player.h types.h object.h set.h
	gcc $(CFLAGS) $<

set.o: set.c types.h set.h
	gcc $(CFLAGS) $<

character.o: character.c character.h types.h
	gcc $(CFLAGS) $<

clean:
	rm -f *.o anthill set_test space_test

clear: 
	rm -f *.o

redo:
	clear;make clean;make

################################################
#                 Test_check                   #
################################################
check:
	valgrind -s --leak-check=full --show-leak-kinds=all ./$(EXE) anthill.dat

set_check:
	./set_test

set_test: set_test.o set.o 
	gcc -o set_test $^

set_test.o: set_test.c set_test.h set.h types.h test.h
	gcc $(CFLAGS) $<

space_check:
	./set_test

space_test: space_test.o space.o set.o object.o
	gcc -o space_test $^

space_test.o: space_test.c space.h types.h object.h set.h space_test.h test.h
	gcc $(CFLAGS) $<

character_test: character_test.o character.o
	gcc -o character_test $^

character_test.o: character_test.c character.h types.h test.h character_test.h
	gcc $(CFLAGS) $<

run:
	./anthill anthill.dat


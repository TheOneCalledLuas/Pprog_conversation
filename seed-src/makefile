EXE = anthill
CFLAGS = -g -Wall -c -ansi -pedantic
CC = gcc

.PHONY = all clean clear check

all: anthill

anthill: command.o game_actions.o game_loop.o game.o game_reader.o graphic_engine.o space.o object.o player.o set.o character.o
	$(CC) -o $(EXE) $^ -L. -lscreen
	
command.o: command.c command.h types.h
	$(CC) $(CFLAGS) $<

game_actions.o: game_actions.c game_actions.h command.h types.h game.h space.h object.h set.h player.h character.h game_reader.h
	$(CC) $(CFLAGS) $<

game_loop.o: game_loop.c command.h types.h game.h space.h object.h set.h player.h character.h game_actions.h game_reader.h graphic_engine.h
	$(CC) $(CFLAGS) $<

game.o: game.c game.h command.h types.h space.h object.h set.h player.h character.h game_reader.h
	$(CC) $(CFLAGS) $<
	
game_reader.o: game_reader.c game_reader.h types.h game.h command.h space.h object.h set.h player.h character.h
	$(CC) $(CFLAGS) $<

graphic_engine.o: graphic_engine.c graphic_engine.h game.h command.h types.h space.h object.h set.h player.h character.h game_reader.h libscreen.h
	$(CC) $(CFLAGS) $<

space.o: space.c space.h types.h object.h set.h
	$(CC) $(CFLAGS) $<

object.o: object.c object.h types.h
	$(CC) $(CFLAGS) $<

player.o: player.c player.h types.h object.h
	$(CC) $(CFLAGS) $<

set.o: set.c types.h set.h
	$(CC) $(CFLAGS) $<

character.o: character.c character.h types.h
	$(CC) $(CFLAGS) $<

clean:
	rm -f *.o anthill set_test space_test character_test

clear: 
	rm -f *.o

redo:
	clear;make clean;make

################################################
#                 Test_check                   #
################################################
test_all: space_test character_test set_test

run_all_test: test_all 
	make set_check; make space_check; make character_check

check:
	valgrind -s --leak-check=full --show-leak-kinds=all ./$(EXE) anthill.dat -l logfile.txt

set_check:
	./set_test

set_test: set_test.o set.o 
	$(CC) -o set_test $^

set_test.o: set_test.c set_test.h set.h types.h test.h
	$(CC) $(CFLAGS) $<

space_check:
	./space_test

space_test: space_test.o space.o set.o object.o
	$(CC) -o space_test $^

space_test.o: space_test.c space.h types.h object.h set.h space_test.h test.h 
	$(CC) $(CFLAGS) $<

character_check:
	./character_test

character_test: character_test.o character.o
	$(CC) -o character_test $^

character_test.o: character_test.c character.h types.h test.h character_test.h
	$(CC) $(CFLAGS) $<

run:
	./anthill anthill.dat


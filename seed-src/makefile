EXE = anthill
CFLAGS = -g -Wall -c -ansi -pedantic

.PHONY = all clean clear check

all: anthill

anthill: command.o game_actions.o game_loop.o game.o game_reader.o graphic_engine.o space.o object.o player.o
	gcc -o $(EXE) $^ -L. -lscreen
	
command.o: command.c command.h types.h
	gcc $(CFLAGS) command.c

game_actions.o: game_actions.c game_actions.h command.h types.h game.h space.h object.h player.h game_reader.h
	gcc $(CFLAGS) game_actions.c

game_loop.o: game_loop.c command.h types.h game.h space.h object.h player.h game_actions.h game_reader.h graphic_engine.h
	gcc $(CFLAGS) game_loop.c

game.o: game.c game.h command.h types.h space.h object.h player.h game_reader.h
	gcc $(CFLAGS) game.c
	
game_reader.o: game_reader.c game_reader.h types.h game.h command.h space.h object.h player.h
	gcc $(CFLAGS) game_reader.c

graphic_engine.o: graphic_engine.c graphic_engine.h game.h command.h types.h space.h object.h player.h game_reader.h libscreen.h
	gcc $(CFLAGS) graphic_engine.c

space.o: space.c space.h types.h object.h
	gcc $(CFLAGS) space.c

object.o: object.c object.h types.h
	gcc $(CFLAGS) object.c

player.o: player.c player.h types.h object.h
	gcc $(CFLAGS) player.c
	
clean:
	rm -f *.o anthill

clear: 
	rm -f *.o

redo:
	clear;make clean;make

check:
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXE) anthill.dat

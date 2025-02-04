EXE = anthill
CFLAGS = -g -Wall -c -ansi -pedantic

anthill: command.o game_actions.o game_loop.o game.o game_reader.o graphic_engine.o space.o object.o
	gcc -o $(EXE) $^ -L. -lscreen
command.o: command.c command.h
	gcc $(CFLAGS) command.c
game_actions.o: game_actions.c game_actions.h
	gcc $(CFLAGS) game_actions.c
game_loop.o: game_loop.c
	gcc $(CFLAGS) game_loop.c
game.o: game.c game.h
	gcc $(CFLAGS) game.c
game_reader.o: game_reader.c game_reader.h
	gcc $(CFLAGS) game_reader.c
graphic_engine.o: graphic_engine.c graphic_engine.h types.h
	gcc $(CFLAGS) graphic_engine.c
space.o: space.c space.h
	gcc $(CFLAGS) space.c
object.o: object.c object.h
	gcc $(CFLAGS) object.c
clean:
	rm -f *.o anthill
redo:
	clear;make clean;make
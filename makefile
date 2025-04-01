EXE = anthill
CFLAGS = -g -Wall -c -ansi -pedantic -Iinclude
DO_OBJ = -o $(OBJDIR)/$@
CC = gcc

#Directories where the files are located.
HEADERDIR = ./include
SRCDIR = ./src
OBJDIR = ./obj
LIBDIR = ./lib
LOGDIR = ./log
TESTDIR = ./test

#List with all the object names
MAKE_OBJ = game_loop.o command.o game_actions.o game.o game_reader.o graphic_engine.o space.o object.o player.o set.o character.o link.o inventory.o

.PHONY = all clean clear check

#Path rules
vpath %.h include
vpath %.c src
vpath %.o obj
vpath %.a lib

all: anthill

anthill:  $(MAKE_OBJ)
	$(CC) -o $(EXE) $(patsubst %.o, $(OBJDIR)/%.o,$(MAKE_OBJ)) -L./$(LIBDIR)/ -lscreen

command.o: command.c command.h types.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

game_actions.o: game_actions.c game_actions.h command.h types.h game.h space.h object.h set.h player.h character.h game_reader.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

game_loop.o: game_loop.c command.h types.h game.h space.h object.h set.h player.h character.h game_actions.h game_reader.h graphic_engine.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

game.o: game.c game.h command.h types.h space.h object.h set.h player.h character.h game_reader.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<
	
game_reader.o: game_reader.c game_reader.h types.h game.h command.h space.h object.h set.h player.h character.h link.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

graphic_engine.o: graphic_engine.c graphic_engine.h game.h command.h types.h space.h object.h set.h player.h character.h game_reader.h libscreen.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

space.o: space.c space.h types.h object.h set.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

object.o: object.c object.h types.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

player.o: player.c player.h types.h object.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

set.o: set.c types.h set.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

character.o: character.c character.h types.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

link.o: link.c link.h types.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

inventory.o: inventory.c set.h inventory.h types.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

clean:
	rm -f $(OBJDIR)/*.o anthill set_test space_test character_test

clear: 
	rm -f $(OBJDIR)/*.o

redo:
	clear;make clean;make

################################################
#                 Test_check                   #
################################################
run_all_test:
	make set_check; make space_check; make character_check

check:
	valgrind -s --leak-check=full --show-leak-kinds=all ./$(EXE) data/anthill.dat -l ./$(LOGDIR)/logfile.txt

set_check:
	make set_test;./set_test

set_test: set_test.o set.o 
	$(CC) -o $@ $^

set_test.o: set_test.c set_test.h set.h types.h test.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

space_check:
	make space_test; ./space_test

space_test: space_test.o space.o set.o object.o
	$(CC) -o space_test $^

space_test.o: space_test.c space.h types.h object.h set.h space_test.h test.h 
	$(CC) $(DO_OBJ) $(CFLAGS) $<

character_check:
	make character_test;./character_test

character_test: character_test.o character.o
	$(CC) -o character_test $^

character_test.o: character_test.c character.h types.h test.h character_test.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

inventory_test: inventory_test.o inventory.o
	$(CC) -o inventory_test $^

inventory_test.o: inventory_test.c inventory_test.h inventory.h types.h test.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

run:
	./anthill data/anthill.dat -l ./log/logfile.txt
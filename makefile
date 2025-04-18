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

.PHONY = all clean clear check redo run run_cmd run_all_test doxygen

#Path rules.
vpath %.h include
vpath %.c src
vpath %.o obj
vpath %.a lib

#Main objectives. 
all: anthill

anthill:  $(MAKE_OBJ)
	$(CC) -o $(EXE) $(patsubst %.o, $(OBJDIR)/%.o,$(MAKE_OBJ)) -L./$(LIBDIR)/ -lscreen

doxygen:
	doxygen Doxyfile

#In order to run individual tests do "make {module_name}_check"
run_all_test:
	make set_check; make space_check; make character_check; make object_check; make inventory_check; make player_check; make link_check

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
	rm -f $(OBJDIR)/*.o anthill set_test space_test character_test object_test inventory_test link_test player_test

clear: 
	rm -f $(OBJDIR)/*.o

redo:
	clear;make clean;make

################################################
#                 Test_check                   #
################################################

check:
	valgrind -s --leak-check=full --show-leak-kinds=all ./$(EXE) data/anthill.dat -l ./$(LOGDIR)/output.log

set_check:
	make clear; make set_test; valgrind -s --leak-check=full --show-leak-kinds=all ./set_test

inventory_check:
	make clear; make inventory_test; valgrind -s --leak-check=full --show-leak-kinds=all ./inventory_test

link_check:
	make clear; make link_test; valgrind -s --leak-check=full --show-leak-kinds=all ./link_test

set_test: set_test.o set.o
	$(CC) -o $@ $(patsubst %.o, $(OBJDIR)/%.o,$^)

set_test.o: set_test.c set_test.h set.h types.h test.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

space_check:
	make clear; make space_test; valgrind -s --leak-check=full --show-leak-kinds=all ./space_test

space_test: space_test.o space.o set.o object.o
	$(CC) -o space_test $(patsubst %.o, $(OBJDIR)/%.o,$^)

space_test.o: space_test.c space.h types.h object.h set.h space_test.h test.h 
	$(CC) $(DO_OBJ) $(CFLAGS) $<

character_check:
	make clear; make character_test;valgrind -s --leak-check=full --show-leak-kinds=all ./character_test

character_test: character_test.o character.o
	$(CC) -o character_test $(patsubst %.o, $(OBJDIR)/%.o,$^)

character_test.o: character_test.c character.h types.h test.h character_test.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

inventory_test: inventory_test.o inventory.o set.o
	$(CC) -o inventory_test $(patsubst %.o, $(OBJDIR)/%.o,$^)

inventory_test.o: inventory_test.c inventory_test.h inventory.h types.h test.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

object_check:
	make clear; make object_test;valgrind -s --leak-check=full --show-leak-kinds=all ./object_test

object_test: object_test.o object.o
	$(CC) -o object_test $(patsubst %.o, $(OBJDIR)/%.o,$^)

object_test.o: object_test.c object_test.h object.h types.h test.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

player_check:
	make clear; make player_test;valgrind -s --leak-check=full --show-leak-kinds=all ./player_test

player_test: player_test.o player.o inventory.o set.o
	$(CC) -o player_test $(patsubst %.o, $(OBJDIR)/%.o,$^)

player_test.o: player_test.c player_test.h player.h types.h test.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

link_test: link_test.o link.o 
	$(CC) -o link_test $(patsubst %.o, $(OBJDIR)/%.o,$^)

link_test.o: link_test.c link_test.h link.h types.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

run:
	./anthill data/anthill.dat -l ./log/output.log

run_cmd:
	./anthill data/anthill.dat -l ./log/output.log < game1.cmd; ./anthill data/anthill.dat -l ./log/output.log < game2.cmd
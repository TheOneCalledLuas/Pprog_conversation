EXE = anthill
CFLAGS = -g -Wall -c -ansi -pedantic -Iinclude
DO_OBJ = -o $@
CC = gcc

#Directories where the files are located.
HEADERDIR = ./include
SRCDIR = ./src
OBJDIR = ./obj
LIBDIR = ./lib
LOGDIR = ./log
TESTDIR = ./test

.PHONY = all clean clear check

all: anthill

anthill: $(OBJDIR)/command.o $(OBJDIR)/game_actions.o $(OBJDIR)/game_loop.o $(OBJDIR)/game.o $(OBJDIR)/game_reader.o $(OBJDIR)/graphic_engine.o $(OBJDIR)/space.o $(OBJDIR)/object.o $(OBJDIR)/player.o $(OBJDIR)/set.o $(OBJDIR)/character.o $(OBJDIR)/link.o $(OBJDIR)/inventory.o
	$(CC) -o $(EXE) $^ -L./$(LIBDIR)/ -lscreen

$(OBJDIR)/command.o: $(SRCDIR)/command.c $(HEADERDIR)/command.h $(HEADERDIR)/types.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

$(OBJDIR)/game_actions.o: $(SRCDIR)/game_actions.c $(HEADERDIR)/game_actions.h $(HEADERDIR)/command.h $(HEADERDIR)/types.h $(HEADERDIR)/game.h $(HEADERDIR)/space.h $(HEADERDIR)/object.h $(HEADERDIR)/set.h $(HEADERDIR)/player.h $(HEADERDIR)/character.h $(HEADERDIR)/game_reader.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

$(OBJDIR)/game_loop.o: $(SRCDIR)/game_loop.c $(HEADERDIR)/command.h $(HEADERDIR)/types.h $(HEADERDIR)/game.h $(HEADERDIR)/space.h $(HEADERDIR)/object.h $(HEADERDIR)/set.h $(HEADERDIR)/player.h $(HEADERDIR)/character.h $(HEADERDIR)/game_actions.h $(HEADERDIR)/game_reader.h $(HEADERDIR)/graphic_engine.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

$(OBJDIR)/game.o: $(SRCDIR)/game.c $(HEADERDIR)/game.h $(HEADERDIR)/command.h $(HEADERDIR)/types.h $(HEADERDIR)/space.h $(HEADERDIR)/object.h $(HEADERDIR)/set.h $(HEADERDIR)/player.h $(HEADERDIR)/character.h $(HEADERDIR)/game_reader.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<
	
$(OBJDIR)/game_reader.o: $(SRCDIR)/game_reader.c $(HEADERDIR)/game_reader.h $(HEADERDIR)/types.h $(HEADERDIR)/game.h $(HEADERDIR)/command.h $(HEADERDIR)/space.h $(HEADERDIR)/object.h $(HEADERDIR)/set.h $(HEADERDIR)/player.h $(HEADERDIR)/character.h $(HEADERDIR)/link.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

$(OBJDIR)/graphic_engine.o: $(SRCDIR)/graphic_engine.c $(HEADERDIR)/graphic_engine.h $(HEADERDIR)/game.h $(HEADERDIR)/command.h $(HEADERDIR)/types.h $(HEADERDIR)/space.h $(HEADERDIR)/object.h $(HEADERDIR)/set.h $(HEADERDIR)/player.h $(HEADERDIR)/character.h $(HEADERDIR)/game_reader.h $(HEADERDIR)/libscreen.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

$(OBJDIR)/space.o: $(SRCDIR)/space.c $(HEADERDIR)/space.h $(HEADERDIR)/types.h $(HEADERDIR)/object.h $(HEADERDIR)/set.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

$(OBJDIR)/object.o: $(SRCDIR)/object.c $(HEADERDIR)/object.h $(HEADERDIR)/types.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

$(OBJDIR)/player.o: $(SRCDIR)/player.c $(HEADERDIR)/player.h $(HEADERDIR)/types.h $(HEADERDIR)/object.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

$(OBJDIR)/set.o: $(SRCDIR)/set.c $(HEADERDIR)/types.h $(HEADERDIR)/set.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

$(OBJDIR)/character.o: $(SRCDIR)/character.c $(HEADERDIR)/character.h $(HEADERDIR)/types.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

$(OBJDIR)/link.o: $(SRCDIR)/link.c $(HEADERDIR)/link.h $(HEADERDIR)/types.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

$(OBJDIR)/inventory.o: $(SRCDIR)/inventory.c $(HEADERDIR)/set.h $(HEADERDIR)/inventory.h $(HEADERDIR)/types.h
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

set_test: $(OBJDIR)/set_test.o $(OBJDIR)/set.o 
	$(CC) -o $@ $^

$(OBJDIR)/set_test.o: $(SRCDIR)/set_test.c $(HEADERDIR)/set_test.h $(HEADERDIR)/set.h $(HEADERDIR)/types.h $(HEADERDIR)/test.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

space_check:
	make space_test; ./space_test

space_test: $(OBJDIR)/space_test.o $(OBJDIR)/space.o $(OBJDIR)/set.o $(OBJDIR)/object.o
	$(CC) -o space_test $^

$(OBJDIR)/space_test.o: $(SRCDIR)/space_test.c $(HEADERDIR)/space.h $(HEADERDIR)/types.h $(HEADERDIR)/object.h $(HEADERDIR)/set.h $(HEADERDIR)/space_test.h $(HEADERDIR)/test.h 
	$(CC) $(DO_OBJ) $(CFLAGS) $<

character_check:
	make character_test;./character_test

character_test: $(OBJDIR)/character_test.o $(OBJDIR)/character.o
	$(CC) -o character_test $^

$(OBJDIR)/character_test.o: $(SRCDIR)/character_test.c $(HEADERDIR)/character.h $(HEADERDIR)/types.h $(HEADERDIR)/test.h $(HEADERDIR)/character_test.h
	$(CC) $(DO_OBJ) $(CFLAGS) $<

run:
	./anthill data/anthill.dat -l ./log/logfile.txt
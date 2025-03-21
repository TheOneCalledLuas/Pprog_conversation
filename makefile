EXE = anthill
CFLAGS = -g -Wall -c -ansi -pedantic
CC = gcc

#Directories where the files are located.
HEADERDIR = lib
SRCDIR = src
OBJDIR = obj
LIBDIR = lib
LOGDIR = log
TESTDIR = test


.PHONY = all clean clear check

all: anthill

anthill: $(OBJDIR)/command.o $(OBJDIR)/game_actions.o $(OBJDIR)/game_loop.o $(OBJDIR)/game.o $(OBJDIR)/game_reader.o $(OBJDIR)/graphic_engine.o $(OBJDIR)/space.o $(OBJDIR)/object.o $(OBJDIR)/player.o $(OBJDIR)/set.o $(OBJDIR)/character.o
	$(CC) -o $(EXE) $^ -L. -lscreen
	
$(OBJDIR)/command.o: $(SRCDIR)/command.c command.h types.h
	$(CC) $(CFLAGS) $<

$(OBJDIR)/game_actions.o: $(SRCDIR)/game_actions.c game_actions.h command.h types.h game.h space.h object.h set.h player.h character.h game_reader.h
	$(CC) $(CFLAGS) $<

$(OBJDIR)/game_loop.o: $(SRCDIR)/game_loop.c command.h types.h game.h space.h object.h set.h player.h character.h game_actions.h game_reader.h graphic_engine.h
	$(CC) $(CFLAGS) $<

$(OBJDIR)/game.o: $(SRCDIR)/game.c game.h command.h types.h space.h object.h set.h player.h character.h game_reader.h
	$(CC) $(CFLAGS) $<
	
$(OBJDIR)/game_reader.o: $(SRCDIR)/game_reader.c game_reader.h types.h game.h command.h space.h object.h set.h player.h character.h
	$(CC) $(CFLAGS) $<

$(OBJDIR)/graphic_engine.o: $(SRCDIR)/graphic_engine.c graphic_engine.h game.h command.h types.h space.h object.h set.h player.h character.h game_reader.h libscreen.h
	$(CC) $(CFLAGS) $<

$(OBJDIR)/space.o: $(SRCDIR)/space.c space.h types.h object.h set.h
	$(CC) $(CFLAGS) $<

$(OBJDIR)/object.o: $(SRCDIR)/object.c object.h types.h
	$(CC) $(CFLAGS) $<

$(OBJDIR)/player.o: $(SRCDIR)/player.c player.h types.h object.h
	$(CC) $(CFLAGS) $<

$(OBJDIR)/set.o: $(SRCDIR)/set.c types.h set.h
	$(CC) $(CFLAGS) $<

$(OBJDIR)/character.o: $(SRCDIR)/character.c character.h types.h
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
	valgrind -s --leak-check=full --show-leak-kinds=all ./$(EXE) anthill.dat -l ./log/logfile.txt

set_check:
	./set_test

set_test: set_test.o set.o 
	$(CC) -o set_test $^

set_test.o: $(SRCDIR)/set_test.c set_test.h set.h types.h test.h
	$(CC) $(CFLAGS) $<

space_check:
	./space_test

space_test: $(SRCDIR)/space_test.o space.o set.o object.o
	$(CC) -o space_test $^

space_test.o: $(SRCDIR)/space_test.c space.h types.h object.h set.h space_test.h test.h 
	$(CC) $(CFLAGS) $<

character_check:
	./character_test

character_test: character_test.o character.o
	$(CC) -o character_test $^

character_test.o: $(SRCDIR)/character_test.c character.h types.h test.h character_test.h
	$(CC) $(CFLAGS) $<

run:
	./anthill anthill.dat -l ./log/logfile.txt


SOURCEDIR = src
HEADERDIR = include
OBJDIR = obj

OBJGAME = $(OBJDIR)/game.o $(OBJDIR)/game_loop.o $(OBJDIR)/command.o $(OBJDIR)/die.o $(OBJDIR)/gameManagement.o $(OBJDIR)/graphic_engine.o $(OBJDIR)/object.o $(OBJDIR)/player.o $(OBJDIR)/screen.o $(OBJDIR)/set.o $(OBJDIR)/space.o $(OBJDIR)/space.o $(OBJDIR)/links.o $(OBJDIR)/inventory.o $(OBJDIR)/dialogue.o

CC = gcc
CFLAGS = -g -Wall -pedantic -I $(HEADERDIR)

EXS = game set_test die_test

.PHONY: all clean clear

all: clear $(EXS) clean

game: $(OBJGAME)
	@echo "==> Compiling and linking $@"
	$(CC) $(CFLAGS) -o $@ $^

set_test: $(OBJDIR)/set_test.o $(OBJDIR)/set.o
	@echo "==> Compiling and linking $@"
	$(CC) $(CFLAGS) -o $@ $^

die_test: $(OBJDIR)/die_test.o $(OBJDIR)/die.o
	@echo "Compiling and linking $@"
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SOURCEDIR)/%.c
	@echo "==> Generating $@"
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo "==> Removing object files"
	rm -f $(OBJDIR)/*.o

clear:
	@echo "==> Removing object files and executables"
	rm -f $(EXS) $(OBJDIR)/*.o

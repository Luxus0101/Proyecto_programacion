game: output
	gcc -o game *.o

output: command.c command.h game.c game.h game_loop.c graphic_engine.c graphic_engine.h screen.c screen.h space.c space.h types.h game_reader.c game_reader.h player.c player.h object.c object.h set.c set.h dice.c dice.h
	gcc -Wall -c  *.c

clean:
	rm *.o

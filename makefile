Game: game_loop.o game.o command.o screen.o graphic_engine.o space.o object.o player.o game_reader.o
	gcc -Wall -pedantic -DDEBUG -o Game game_loop.o game.o screen.o command.o graphic_engine.o space.o object.o player.o game_reader.o

Set_test: set.o set_test.o
	gcc -Wall -pedantic -DDEBUG -o Set_test set.o set_test.o

Die_test: die.o die_test.o
	gcc -Wall -pedantic -DDEBUG -o Die_test die.o die_test.o

game_loop.o: game_loop.c
	gcc -Wall -pedantic -DDEBUG -c game_loop.c

game.o: game.c
	gcc  -Wall -pedantic -DDEBUG -c game.c

command.o: command.c
	gcc -Wall -pedantic -DDEBUG -c command.c

screen.o: screen.c
	gcc -Wall -pedantic -DDEBUG -c  screen.c

graphic_engine.o: graphic_engine.c
	gcc -Wall -pedantic -DDEBUG -c  graphic_engine.c

space.o: space.c
	gcc -Wall -pedantic -DDEBUG -c space.c

player.o: player.c
	gcc -Wall -pedantic -DDEBUG -c  player.c

object.o: object.c
	gcc -Wall -pedantic -DDEBUG -c  object.c

game_reader.o: game_reader.c
	gcc -Wall -pedantic -DDEBUG -c game_reader.c

set_test.o: set_test.c
	gcc -Wall -pedantic -DDEBUG -c set_test.c

set.o: set.c
	gcc -Wall -pedantic -DDEBUG -c set.c

die_test.o: die_test.c
	gcc -Wall -pedantic -DDEBUG -c die_test.c

die.o: die.c
	gcc -Wall -pedantic -DDEBUG -c die.c


clean:
	rm -f *.o

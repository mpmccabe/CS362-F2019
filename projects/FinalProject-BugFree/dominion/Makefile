CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

unittests: bug1.c bug2.c bug3.c bug4.c bug8.c bug5.c bug7.c bug9.c bug10.c dominion.o rngs.o interface.o
	gcc -o bug1 -g  bug1.c dominion.o rngs.o $(CFLAGS)
	gcc -o bug2 -g  bug2.c dominion.o rngs.o $(CFLAGS)
	gcc -o bug3 -g  bug3.c dominion.o rngs.o $(CFLAGS)
	gcc -o bug4 -g  bug4.c dominion.o rngs.o $(CFLAGS)
	gcc -o bug5 -g  bug5.c dominion.o rngs.o $(CFLAGS)
	gcc -o bug8 -g bug8.c dominion.o rngs.o $(CFLAGS)
	gcc -o bug7 -g bug7.c dominion.o rngs.o $(CFLAGS)
	gcc -o bug9 -g bug9.c dominion.o rngs.o $(CFLAGS)
	gcc -o bug10 -g bug10.c dominion.o rngs.o $(CFLAGS)

runalltests: unittests
	./bug1 >> unittestresults.out
	./bug2 >> unittestresults.out
	./bug3 >> unittestresults.out
	./bug4 >> unittestresults.out
	./bug5 >> unittestresults.out
	./bug7 >> unittestresults.out
	./bug8 >> unittestresults.out
	./bug9 >> unittestresults.out
	./bug10 >> unittestresults.out

unittestresults: runalltests
	gcov dominion.c -f -b >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe bug1 bug1.exe bug2 bug2.exe bug3 bug3.exe bug4 bug4.exe bug5 bug5.exe bug8 bug8.exe bug7 bug7.exe bug9 bug9.exe bug10 bug10.exe


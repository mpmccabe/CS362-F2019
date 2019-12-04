CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

unittests: bug8.c bug5.c bug7.c bug9.c bug10.c dominion.o rngs.o
	gcc -o bug5 -g  bug5.c dominion.o rngs.o $(CFLAGS)
	gcc -o bug8 -g bug8.c dominion.o rngs.o $(CFLAGS)
	gcc -o bug7 -g bug7.c dominion.o rngs.o $(CFLAGS)
	gcc -o bug9 -g bug9.c dominion.o rngs.o $(CFLAGS)
	gcc -o bug10 -g bug10.c dominion.o rngs.o $(CFLAGS)
	
runalltests: unittests
	./bug5 >> randomtestresults.out
	./bug7 >> randomtestresults.out
	./bug8 >> randomtestresults.out
	./bug9 >> randomtestresults.out
	./bug10 >> randomtestresults.out

testresults: runalltests
	gcov dominion.c -f -b >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

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
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe

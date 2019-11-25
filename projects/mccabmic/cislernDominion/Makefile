CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

randomtests: randomtestcard1.c randomtestcard2.c randomtestcard3.c dominion.o rngs.o
	gcc  -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	gcc  -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	gcc  -o randomtestcard3 -g  randomtestcard3.c dominion.o rngs.o $(CFLAGS)

unitTests: unittestone.c unittesttwo.c unittestthree.c unittestfour.c dominion.o rngs.o
	gcc -o unittestone -g unittestone.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittesttwo -g unittesttwo.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittestthree -g unittestthree.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittestfour -g unittestfour.c dominion.o rngs.o $(CFLAGS)

runallunittests: unitTests
	./unittestone >> unittestresult.out
	./unittesttwo >> unittestresult.out
	./unittestthree >> unittestresult.out 
	./unittestfour >> unittestresult.out

runallrandomtests: randomtests
	./randomtestcard1 >> randomtestresults.out
	./randomtestcard2 >> randomtestresults.out
	./randomtestcard3 >> randomtestresults.out

randomtestresults: runallrandomtests
	gcov dominion.c -f -b >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe

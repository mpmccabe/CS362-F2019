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

unitTests: unittestone.c unittesttwo.c unittestthree.c unittestfour.c dominion.o rngs.o
	gcc -o unittestone -g unittestone.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittesttwo -g unittesttwo.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittestthree -g unittestthree.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittestfour -g unittestfour.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runalltests: unitTests
	./unittestone >> unittestresult.out 2>&1
	./unittesttwo >> unittestresult.out 2>&1
	./unittestthree >> unittestresult.out 2>&1
	./unittestfour >> unittestresult.out 2>&1

unittestresults: runalltests
	gcov dominion.c -f -b >> unittestresult.out 2>&1
	cat dominion.c.gcov >> unittestresult.out 2>&1

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittestone unittesttwo unittestthree unittestfour unittestone.exe unittesttwo.exe unittestthree.exe unittestfour.exe

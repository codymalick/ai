CC=clang++
CFLAGS=-g -Wall

all: ai_mc clean

ai_mc: main.o world.o alg.o
	$(CC) main.o world.o alg.o -o ai_mc
	
main.o: main.cpp
	$(CC) main.cpp -c $(CFLAGS)
	
world.o: world.h world.cpp
	$(CC) world.cpp -c $(CFLAGS)
	
alg.o: alg.h alg.cpp
	$(CC) alg.cpp -c $(CFLAGS)

clean:
	rm -f *.o
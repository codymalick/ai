CC=clang++
CFLAGS=-g -Wall -std=c++11
# TODO: Build directory

all: ai_mc 

ai_mc: main.o world.o solver.o alg.o aux.o
	$(CC) main.o world.o solver.o alg.o aux.o -o ai_mc

worldtest: wtest.o world.o
	$(CC) wtest.o world.o -o worldtest


wtest.o: wtest.cpp
	$(CC) wtest.cpp -c $(CFLAGS)
	
main.o: main.cpp
	$(CC) main.cpp -c $(CFLAGS)
	
world.o: world.h world.cpp
	$(CC) world.cpp -c $(CFLAGS)
	
solver.o: solver.h solver.cpp
	$(CC) solver.cpp -c $(CFLAGS)
	
alg.o: alg.h alg.cpp
	$(CC) alg.cpp -c $(CFLAGS)

aux.o: aux.h aux.cpp
	$(CC) aux.cpp -c $(CFLAGS)


clean:
	rm -f *.o ai_mc worldtest
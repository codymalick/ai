CC = clang++
CFLAGS = -std=c++0x -Wall

all: othello


othello: GameDriver.o Board.o OthelloBoard.o Player.o HumanPlayer.o MinimaxPlayer.o
	$(CC) $(CFLAGS) GameDriver.o Board.o OthelloBoard.o Player.o HumanPlayer.o MinimaxPlayer.o -o othello


GameDriver.o: GameDriver.cpp GameDriver.h
	$(CC) -c GameDriver.cpp $(CFLAGS)

Board.o: Board.cpp Board.h
	$(CC) -c Board.cpp $(CFLAGS)

OthelloBoard.o: OthelloBoard.cpp OthelloBoard.h
	$(CC) -c OthelloBoard.cpp $(CFLAGS)

Player.o: Player.cpp Player.h
	$(CC) -c Player.cpp $(CFLAGS)

HumanPlayer.o: HumanPlayer.cpp HumanPlayer.h
	$(CC) -c HumanPlayer.cpp $(CFLAGS)

MinimaxPlayer.o: MinimaxPlayer.cpp MinimaxPlayer.h
	$(CC) -c MinimaxPlayer.cpp $(CFLAGS)


clean:
	rm -f othello *.o

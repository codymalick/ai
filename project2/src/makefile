CC = clang++
CFLAGS = -std=c++0x -Wall

all: othello


othello: GameDriver.o Board.o OthelloBoard.o Player.o HumanPlayer.o MinimaxPlayer.o
	$(CC) $(CFLAGS) GameDriver.o Board.o OthelloBoard.o Player.o HumanPlayer.o MinimaxPlayer.o -o othello


GameDriver.o: GameDriver.cpp GameDriver.h OthelloBoard.o Player.o HumanPlayer.o MinimaxPlayer.o
	$(CC) -c GameDriver.cpp $(CFLAGS)

HumanPlayer.o: HumanPlayer.cpp HumanPlayer.h OthelloBoard.o Player.o
	$(CC) -c HumanPlayer.cpp $(CFLAGS)

MinimaxPlayer.o: MinimaxPlayer.cpp MinimaxPlayer.h OthelloBoard.o Player.o
	$(CC) -c MinimaxPlayer.cpp $(CFLAGS)

Player.o: Player.cpp Player.h OthelloBoard.o
	$(CC) -c Player.cpp $(CFLAGS)

OthelloBoard.o: OthelloBoard.cpp OthelloBoard.h Board.o
	$(CC) -c OthelloBoard.cpp $(CFLAGS)

Board.o: Board.cpp Board.h
	$(CC) -c Board.cpp $(CFLAGS)


clean:
	rm -f othello *.o

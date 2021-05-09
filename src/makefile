OBJS	= main.o Board.o Tile.o Cell.o Dictionary.o
SOURCE	= main.cpp Scrabble/Board.cpp Scrabble/Tile.cpp Scrabble/Cell.cpp Scrabble/Dictionary.cpp
HEADER	= Scrabble/Board.h Scrabble/Tile.h Scrabble/BoardPosition.h Scrabble/Cell.h Scrabble/Dictionary.h Scrabble/Scrabble.h
OUT	= main
CC	 = g++
FLAGS	 = -g -c -Wall

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c++11

Board.o: Scrabble/Board.cpp
	$(CC) $(FLAGS) Scrabble/Board.cpp -std=c++11

Tile.o: Scrabble/Tile.cpp
	$(CC) $(FLAGS) Scrabble/Tile.cpp -std=c++11

Cell.o: Scrabble/Cell.cpp
	$(CC) $(FLAGS) Scrabble/Cell.cpp -std=c++11

Dictionary.o: Scrabble/Dictionary.cpp
	$(CC) $(FLAGS) Scrabble/Dictionary.cpp -std=c++11

clean:
	rm -f $(OBJS) $(OUT)

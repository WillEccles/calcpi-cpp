CC=g++
SRC=calcpi.cpp
FLAGS=-std=c++11 -Os
OUTPUT=calcpi.o

all:
	$(CC) $(SRC) -o $(OUTPUT) $(FLAGS)

clean:
	rm calcpi.o

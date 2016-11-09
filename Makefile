CC=g++
SRC=main.cpp
FLAGS=-std=c++11 -Os
OUTPUT=build/calcpi.o

all:
	$(CC) $(SRC) -o $(OUTPUT) $(FLAGS)

clean:
	-rm -rf build
	-rm -rf release

# used to create releases for github.com/willeccles/calcpi-cpp
release:
	$(CC) $(SRC) -o release/calcpi $(FLAGS)

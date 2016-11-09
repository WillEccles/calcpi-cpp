CC=g++
SRC=main.cpp
FLAGS=-std=c++11 -Os -stdlib=libc++
OUTPUT=calcpi.o

all:
	$(CC) $(SRC) -o $(OUTPUT) $(FLAGS)

clean:
	-rm calcpi.*
	-rm calcpi

# used to create releases for github.com/willeccles/calcpi-cpp
release:
	$(CC) $(SRC) -o calcpi $(FLAGS)
	zip calcpi.zip calcpi

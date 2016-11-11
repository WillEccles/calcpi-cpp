CC=g++
SRC=main.cpp
FLAGS=-std=c++11 -O3 -stdlib=libc++ -fwhole-program -DNDEBUG -s
OUTPUT=calcpi.o

all:
	$(CC) $(SRC) -o $(OUTPUT) $(FLAGS) -march=native

clean:
	-rm calcpi.*
	-rm calcpi

# used to create releases for github.com/willeccles/calcpi-cpp
release:
	$(CC) $(SRC) -o calcpi $(FLAGS)
	zip calcpi.zip calcpi

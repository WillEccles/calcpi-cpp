SRC=main.cpp
FLAGS=-std=c++11 -O3 -fwhole-program -s -lpthread
OUTPUT=calcpi.o

all: $(SRC)
	$(CXX) $< -o $(OUTPUT) $(FLAGS) -march=native

clean:
	-rm -f calcpi.*
	-rm -f calcpi

# used to create releases for github.com/willeccles/calcpi-cpp
release:
	$(CXX) $(SRC) -o calcpi $(FLAGS)
	zip calcpi.zip calcpi

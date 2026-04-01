CC = g++
CFLAGS = -Wall -std=c++11

all: binpack

binpack: main.o BinPacker.o
	$(CC) $(CFLAGS) main.o BinPacker.o -o binpack

main.o: main.cpp BinPacker.hpp Bin.hpp
	$(CC) $(CFLAGS) -c main.cpp

BinPacker.o: BinPacker.cpp BinPacker.hpp Bin.hpp
	$(CC) $(CFLAGS) -c BinPacker.cpp

clean:
	rm -f *.o binpack
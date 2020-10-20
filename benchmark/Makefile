CC=g++
CFLAGS=-std=c++17 -O3 -march=native
CVEC=-ftree-loop-vectorize
CNOVEC=-fno-tree-loop-vectorize
all: vec novec assembly
MUL=FMA
vec: main.cpp
	$(CC) main.cpp -D$(MUL) -DVEC=1 $(CFLAGS) -o vec
novec: main.cpp
	$(CC) main.cpp -D$(MUL) -DSERIAL=1 $(CFLAGS) $(CNOVEC) -o novec
assembly: 
	$(CC) main.cpp -D$(MUL) $(CFLAGS)  -S -o vec.s
	$(CC) main.cpp -D$(MUL) $(CFLAGS) $(CNOVEC) -S -o novec.s
clean:
	rm vec novec vec-benchmark.data ser-benchmark.data vec.s novec.s

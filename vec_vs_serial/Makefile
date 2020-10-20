CC=clang++
CFLAGS=-std=c++17 -O3 -march=native
CVEC=-ftree-loop-vectorize -Rpass-analysis=loop-vectorize
CNOVEC=-fno-slp-vectorize -fno-tree-vectorize #-fno-tree-loop-vectorize
all: vec novec assembly
MUL=MUL
vec: main.cpp
	$(CC) main.cpp -D$(MUL) -DVEC=1 $(CFLAGS) -o vec
novec: main.cpp
	$(CC) main.cpp -D$(MUL) -DSERIAL=1 $(CFLAGS) $(CNOVEC) -o novec
assembly: 
	$(CC) main.cpp -D$(MUL) $(CFLAGS) -Rpass-analysis=loop-vectorize -S -o vec.s
	$(CC) main.cpp -D$(MUL) $(CFLAGS) $(CNOVEC) -S -o novec.s
clean:
	rm vec novec
	rm vec-benchmark.data ser-benchmark.data
	rm vec.s novec.s

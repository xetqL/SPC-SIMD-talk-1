#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#define NTIMES 50
#define SIZE 10'000'000
#define Real float

#ifdef SERIAL
std::string benchmark_fname("ser-benchmark.data");
#else
std::string benchmark_fname("vec-benchmark.data");
#endif

template<int x, int y>
struct is_divisible_by {
	static constexpr bool value = ((x%y) == 0);
};
/**
* write the average time to compute the loop where each iteration cost
* n flop
*/
void write_benchmark_data(int nflop, std::tuple<double, double, double> data){
	auto[min, max, avg_time] = data;
	std::ofstream ofdata;
	ofdata.open(benchmark_fname, std::ofstream::out | std::ofstream::app);
	ofdata << nflop << " " << min<< " " << max << " " << avg_time << std::endl;
	ofdata.close();
}
/**
* Recursively generate a code that cost X flop.
* The computation is in the form: a*b*a*b*a*b
*/
template<int N>
inline constexpr Real muladd_flops(const Real a, const Real b){
	if constexpr(N==1) 
		return b;
    else if constexpr(is_divisible_by<N, 2>::value) 
		return muladd_flops<N-1>(b, a) * b;
    else
		return muladd_flops<N-1>(b, a) + b;
}

template<int N>
inline constexpr Real X_flops(const Real a, const Real b){
	if constexpr(N==1) 
		return b;
    else
		return X_flops<N-1>(b, a) * b;
}


template<unsigned NFLOPS>
std::tuple<double, double, double> benchmark() {
	Real *a = (Real*) aligned_alloc(32, SIZE*sizeof(Real));
	Real *b = (Real*) aligned_alloc(32, SIZE*sizeof(Real));
	Real *c = (Real*) aligned_alloc(32, SIZE*sizeof(Real));
    Real scalar = 3.0;
    for(size_t i = 0; i < SIZE; ++i) {
        a[i] = 1.0; b[i] = 2.0;
    }
    double avg_time = 0.0, 
		min=std::numeric_limits<Real>::max(), 
		max=std::numeric_limits<Real>::lowest();    
    for(size_t k = 0; k<NTIMES; ++k) {
        clock_t begin = clock();
		#pragma GCC ivdep
		for(size_t i=0; i<SIZE; ++i) {
#ifdef MUL
			c[i] = X_flops<NFLOPS+1>(a[i], b[i]); 
#else
			c[i] = muladd_flops<2*NFLOPS+1>(a[i], b[i]);
#endif
}
        clock_t end = clock();
		double T = (double) (end-begin) / CLOCKS_PER_SEC;
        avg_time += T / NTIMES;
		min = std::min(min, T);
		max = std::max(max, T);
        c[1] = c[2];
    }
	delete a;
	delete b;
	delete c;

	return std::make_tuple(min, max, avg_time);
}

int main(int argc, char* argv[]){

	write_benchmark_data (1,  benchmark<1> ());
	write_benchmark_data (2,  benchmark<2> ());
	write_benchmark_data (4,  benchmark<4> ());
	write_benchmark_data (6,  benchmark<6> ());
	write_benchmark_data (8,  benchmark<8> ());
	write_benchmark_data(12,  benchmark<12>());
	write_benchmark_data(16,  benchmark<16>());
	write_benchmark_data(32,  benchmark<32>());
	write_benchmark_data(48,  benchmark<48>());
	write_benchmark_data(64,  benchmark<64>());
	write_benchmark_data(128, benchmark<128>());
	write_benchmark_data(256, benchmark<256>());
 
	return 0;
}

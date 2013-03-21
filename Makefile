PPXFLAGS = -DPPXHOST=\"$(PPX_LVHOST)\"

avx : avx_bench.cpp
	g++ $(PPXFLAGS) -fopenmp -mavx -O3 -o avx avx_bench.cpp

sse : sse_bench.cpp
	icpc $(PPXFLAGS) -openmp -o sse sse_bench.cpp

scalar : scalar_bench.cpp
	icpc $(PPXFLAGS) -openmp -o scalar scalar_bench.cpp

clean :
	rm -f avx sse

PPXFLAGS = -DPPXHOST=\"$(PPX_LVHOST)\"

UNROLLS = 1
KERNEL = ./kernels/c_original.cpp

all : avx

avx_kernel.o : avx_kernel.h avx_kernel.cpp
	rm -f kernel_include.cpp
	for i in `seq 1 $(UNROLLS)`; do cat $(KERNEL) >> kernel_include.cpp; done
	icc $(PPXFLAGS) -DUNROLLS=$(UNROLLS) -fopenmp -mavx -O3 -c -o avx_kernel.o avx_kernel_simple.cpp

avx_bench.o : avx_bench.cpp
	icc $(PPXFLAGS) -fopenmp -mavx -O3 -c -o avx_bench.o avx_bench.cpp

avx : avx_bench.o avx_kernel.o
	icc $(PPXFLAGS) -fopenmp -mavx -O3 -o avx avx_bench.o avx_kernel.o

sse : sse_bench.cpp
	icpc $(PPXFLAGS) -openmp -o sse sse_bench.cpp

scalar : scalar_bench.cpp
	icpc $(PPXFLAGS) -openmp -o scalar scalar_bench.cpp

clean :
	rm -f avx sse
	rm -f avx_kernel.o
	rm -f avx_bench.o
	rm -f avx_kernel_many.s
	rm -f kernel_include.s

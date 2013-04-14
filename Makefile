PPXFLAGS = -DPPXHOST=\"$(PPX_LVHOST)\"

UNROLLS = 20
KERNEL = ./kernels/asm_multOnly.cpp
KERNEL_INCLUDE = kernel_include.cpp

all : avx

$(KERNEL_INCLUDE) : $(KERNEL)
	rm -f $(KERNEL_INCLUDE)
	for i in `seq 1 $(UNROLLS)`; do cat $(KERNEL) >> $(KERNEL_INCLUDE); done
	touch $(KERNEL)

avx_kernel.o : avx_kernel.cpp $(KERNEL_INCLUDE)
	icc -DUNROLLS=$(UNROLLS) -fopenmp -mavx -O3 -c -o $@ $<

avx_kernel_aica.o : avx_kernel.cpp $(KERNEL_INCLUDE)
	icc -g -DUSE_IACA=1 -DUNROLLS=$(UNROLLS) -fopenmp -mavx -O3 -c -o $@ $<

init_array.o : init_array.cpp
	icc $(PPXFLAGS) -fopenmp -mavx -O3 -c -o init_array.o init_array.cpp

avx_bench.o : avx_bench.cpp
	icc $(PPXFLAGS) -fopenmp -mavx -O3 -c -o avx_bench.o avx_bench.cpp

avx : avx_bench.o avx_kernel.o init_array.o
	icc $(PPXFLAGS) -fopenmp -mavx -O3 -o avx avx_bench.o avx_kernel.o init_array.o

sse : sse_bench.cpp
	icpc $(PPXFLAGS) -openmp -o sse sse_bench.cpp

scalar : scalar_bench.cpp
	icpc $(PPXFLAGS) -openmp -o scalar scalar_bench.cpp

aica : avx_kernel_aica.o
	iaca -64 -arch IVB -o out.txt $^

clean :
	rm -f avx sse
	rm -f avx_kernel.o
	rm -f avx_bench.o
	rm -f init_array.o
	rm -f $(KERNEL_INCLUDE)

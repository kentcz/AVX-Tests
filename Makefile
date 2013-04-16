PPXFLAGS = -DPPXHOST=\"$(PPX_LVHOST)\"

UNROLLS = 100
KERNEL = ./kernels/asm_original.asm
KERNEL_INCLUDE = kernel_include.cpp

all : avx

$(KERNEL_INCLUDE) : $(KERNEL)
	rm -f $(KERNEL_INCLUDE)
	for i in `seq 1 $(UNROLLS)`; do cat $(KERNEL) >> $(KERNEL_INCLUDE); done
	touch $(KERNEL)

avx_kernel.old : avx_kernel.cpp $(KERNEL_INCLUDE)
	icc -DUNROLLS=$(UNROLLS) -fopenmp -mavx -O3 -c -o $@ $<

avx_kernel.o : avx_kernel.asm
	yasm -dKERNEL=$(KERNEL) -dUNROLLS=$(UNROLLS) -f elf64 -o $@ $<

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

test_kernel.o : test_kernel.cpp simple_kernel.h
	icc -g -mavx -c -o $@ $<

test : test_kernel.o simple_kernel.o
	icpc -mavx -O3 -o $@ $^

simple_kernel.o : simple_kernel.asm
	yasm -f elf64 -o $@ $<
	#icc -mavx -O0 -S -o $@.asm $<
	#icc -mavx -O0 -c -o $@ $<

simple.o : simple.asm
	yasm -f elf64 -l simple.lst -o $@ $<

simple : simple.o
	#gcc -lc -o $@ $^
	ld -lc -o $@ $^
	

clean :
	rm -f avx sse
	rm -f avx_kernel.o
	rm -f avx_bench.o
	rm -f init_array.o
	rm -f simple_kernel.o
	rm -f $(KERNEL_INCLUDE)

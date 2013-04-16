#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>
#include <sys/time.h>
#include <omp.h>
#include <math.h>

#include "avx_kernel.h"

#include "/home/mic/PPX/Benchmarks/include/tsc.h"
#include "/home/mic/PPX/Benchmarks/include/ppx_sockets.h"


#include <iostream>
using namespace std;

void init_array(double *arr) {
	for (int i=0; i < 64; i++) {
		arr[i] = (double) 1.0001 + (0.00001 * (4*atan(1.0)) * i);
	}
}

//
// Used to get the time (in miliseconds)
//
double mdsecnd(void)
{
          static double base;
          struct timeval t;
          double td;
          gettimeofday(&t, NULL);
          td = t.tv_sec+t.tv_usec*1.0e-6;
          if (!base)
            base = td;
          return td-base;
}

double run_test(int tds,size_t iterations, int printStats){

	// Initialize kernel values
	double *vals = (double *) malloc(sizeof(double) * 64 * tds);
	for (int w=0; w < tds; w++) {
		init_array( &(vals[w*64]) );
	}

	// Create array for return values
    double *sum = (double*)malloc(tds * sizeof(double));

	double start = mdsecnd();

	#pragma omp parallel num_threads(tds)
    {
		int thread_id = omp_get_thread_num();
        double ret = avx_kernel( &(vals[thread_id*64]), iterations);
        sum[omp_get_thread_num()] = vals[thread_id*64];
    }

    double stop = mdsecnd();
    double secs = stop - start;

	// Calculate the number of flops
	//   - Each iteration contains 48,000 instructions
	//   - Each instruction contains 4 flops
    unsigned long long ops = 48 * 1000 * iterations * tds * 4;


    if (printStats == 0) {
    	cout << "Threads = " << tds << endl;
    	cout << "Seconds = " << secs << endl;
    	cout << "FP Ops  = " << ops << endl;
    	cout << "FLOPs   = " << ops / secs << endl;
    }

    double out = 0;
    int c = 0;
    while (c < tds){
        out += sum[c++];
    }

    cout << "sum = " << out << endl;
    
    if (printStats == 0) {
    	cout << endl;
    }

    free(sum);
    free(vals);
    return ((double) ops) / secs;
}



//
// Arg[1] - Number of threads
// Arg[2] - Number of iterations
// Arg[3] - Time to run (in seconds)
//
//  There are two mode: set Iterations or set Time
//  If Time is set, then the number of iterations does not matter
//
int main(int argc, const char* argv[]) {
    
	double start;
	
  	int sec = 0;
	int iters = 5;	
	int threads = 4;	

	if (argc >= 2) threads = atoi(argv[1]);
	if (argc >= 3) iters = atoi(argv[2]);
	if (argc >= 4) sec = atoi(argv[3]);

	// Mode 1 : Fixed Time
	if (sec != 0) {
        	//warmup	
		start = mdsecnd();
		while (mdsecnd() - start < sec ) {
			run_test(threads,2e6,1);
		}



		printf("warmup complete %f\n",mdsecnd() - start);
		//socket_send("StartAVX\n");
		tsc_start();

        	//test	
		start = mdsecnd();
		while (mdsecnd() - start < sec ) {
			// Run for 2 million iterations, then check time
			run_test(threads,2e6,1);
		}
		
		tsc_stop();
		//socket_send("StopAVX");
		tsc_print();
	} 
	
	// Mode 2 : Fixed Iterations
	else {
		run_test(threads,iters * 1e6,0);
	}

	return 0;
}

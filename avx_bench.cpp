#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>
#include <sys/time.h>
#include <omp.h>

#include "../include/tsc.h"
#include "../include/ppx_sockets.h"


#include <iostream>
using namespace std;

double test_AVX(double x,double y,size_t iterations){
    register __m256d r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,rA,rB,rC,rD,rE,rF;

    //  Generate starting data.
    r0 = _mm256_set1_pd(x);
    r1 = _mm256_set1_pd(y);

    r8 = _mm256_set1_pd(-0.0);

    r2 = _mm256_xor_pd(r0,r8);
    r3 = _mm256_or_pd(r0,r8);
    r4 = _mm256_andnot_pd(r8,r0);
    r5 = _mm256_mul_pd(r1,_mm256_set1_pd(0.37796447300922722721));
    r6 = _mm256_mul_pd(r1,_mm256_set1_pd(0.24253562503633297352));
    r7 = _mm256_mul_pd(r1,_mm256_set1_pd(4.1231056256176605498));
    r8 = _mm256_add_pd(r0,_mm256_set1_pd(0.37796447300922722721));
    r9 = _mm256_add_pd(r1,_mm256_set1_pd(0.24253562503633297352));
    rA = _mm256_sub_pd(r0,_mm256_set1_pd(4.1231056256176605498));
    rB = _mm256_sub_pd(r1,_mm256_set1_pd(4.1231056256176605498));

    rC = _mm256_set1_pd(1.4142135623730950488);
    rD = _mm256_set1_pd(1.7320508075688772935);
    rE = _mm256_set1_pd(0.57735026918962576451);
    rF = _mm256_set1_pd(0.70710678118654752440);

    unsigned long long iMASK = 0x800fffffffffffffull;
    __m256d MASK = _mm256_set1_pd(*(double*)&iMASK);
    __m256d vONE = _mm256_set1_pd(1.0);

    size_t c = 0;
    while (c < iterations){
        size_t i = 0;
        while (i < 1000){
            //  Here's the meat - the part that really matters.
            r0 = _mm256_add_pd(r0,rF);
            r1 = _mm256_mul_pd(r1,rE);
	    r2 = _mm256_sub_pd(r2,rD);
            r3 = _mm256_mul_pd(r3,rC);
#ifndef ILP2
            r4 = _mm256_add_pd(r4,rF);
            r5 = _mm256_mul_pd(r5,rE);
#endif
#ifndef ILP
            r6 = _mm256_sub_pd(r6,rD);
            r7 = _mm256_mul_pd(r7,rC);
            r8 = _mm256_add_pd(r8,rF);
            r9 = _mm256_mul_pd(r9,rE);
            rA = _mm256_sub_pd(rA,rD);
            rB = _mm256_mul_pd(rB,rC);
#endif

            r0 = _mm256_mul_pd(r0,rC);
            r1 = _mm256_add_pd(r1,rD);
	    r2 = _mm256_mul_pd(r2,rE);
            r3 = _mm256_sub_pd(r3,rF);
#ifndef ILP2
            r4 = _mm256_mul_pd(r4,rC);
            r5 = _mm256_add_pd(r5,rD);
#endif
#ifndef ILP
            r6 = _mm256_mul_pd(r6,rE);
            r7 = _mm256_sub_pd(r7,rF);
            r8 = _mm256_mul_pd(r8,rC);
            r9 = _mm256_add_pd(r9,rD);
            rA = _mm256_mul_pd(rA,rE);
            rB = _mm256_sub_pd(rB,rF);
#endif

            r0 = _mm256_add_pd(r0,rF);
            r1 = _mm256_mul_pd(r1,rE);
	    r2 = _mm256_sub_pd(r2,rD);
            r3 = _mm256_mul_pd(r3,rC);
#ifndef ILP2
            r4 = _mm256_add_pd(r4,rF);
            r5 = _mm256_mul_pd(r5,rE);
#endif
#ifndef ILP
            r6 = _mm256_sub_pd(r6,rD);
            r7 = _mm256_mul_pd(r7,rC);
            r8 = _mm256_add_pd(r8,rF);
            r9 = _mm256_mul_pd(r9,rE);
            rA = _mm256_sub_pd(rA,rD);
            rB = _mm256_mul_pd(rB,rC);
#endif

            r0 = _mm256_mul_pd(r0,rC);
            r1 = _mm256_add_pd(r1,rD);
	    r2 = _mm256_mul_pd(r2,rE);
            r3 = _mm256_sub_pd(r3,rF);
#ifndef ILP2
            r4 = _mm256_mul_pd(r4,rC);
            r5 = _mm256_add_pd(r5,rD);
#endif
#ifndef ILP
            r6 = _mm256_mul_pd(r6,rE);
            r7 = _mm256_sub_pd(r7,rF);
            r8 = _mm256_mul_pd(r8,rC);
            r9 = _mm256_add_pd(r9,rD);
            rA = _mm256_mul_pd(rA,rE);
            rB = _mm256_sub_pd(rB,rF);
#endif

            i++;
        }

        //  Need to renormalize to prevent denormal/overflow.
        r0 = _mm256_and_pd(r0,MASK);
        r1 = _mm256_and_pd(r1,MASK);
        r2 = _mm256_and_pd(r2,MASK);
        r3 = _mm256_and_pd(r3,MASK);
        r4 = _mm256_and_pd(r4,MASK);
        r5 = _mm256_and_pd(r5,MASK);
        r6 = _mm256_and_pd(r6,MASK);
        r7 = _mm256_and_pd(r7,MASK);
        r8 = _mm256_and_pd(r8,MASK);
        r9 = _mm256_and_pd(r9,MASK);
        rA = _mm256_and_pd(rA,MASK);
        rB = _mm256_and_pd(rB,MASK);
        r0 = _mm256_or_pd(r0,vONE);
        r1 = _mm256_or_pd(r1,vONE);
        r2 = _mm256_or_pd(r2,vONE);
        r3 = _mm256_or_pd(r3,vONE);
        r4 = _mm256_or_pd(r4,vONE);
        r5 = _mm256_or_pd(r5,vONE);
        r6 = _mm256_or_pd(r6,vONE);
        r7 = _mm256_or_pd(r7,vONE);
        r8 = _mm256_or_pd(r8,vONE);
        r9 = _mm256_or_pd(r9,vONE);
        rA = _mm256_or_pd(rA,vONE);
        rB = _mm256_or_pd(rB,vONE);

        c++;
    }

    r0 = _mm256_add_pd(r0,r1);
    r2 = _mm256_add_pd(r2,r3);
    r4 = _mm256_add_pd(r4,r5);
    r6 = _mm256_add_pd(r6,r7);
    r8 = _mm256_add_pd(r8,r9);
    rA = _mm256_add_pd(rA,rB);

    r0 = _mm256_add_pd(r0,r2);
    r4 = _mm256_add_pd(r4,r6);
    r8 = _mm256_add_pd(r8,rA);

    r0 = _mm256_add_pd(r0,r4);
    r0 = _mm256_add_pd(r0,r8);

    //  Prevent Dead Code Elimination
    double out = 0;
    out += ((double*)&r0)[0];
    out += ((double*)&r0)[1];
    out += ((double*)&r0)[2];
    out += ((double*)&r0)[3];

    return out;
}

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

double test_dp_mac_AVX(int tds,size_t iterations, int warmup){

    double *sum = (double*)malloc(tds * sizeof(double));
    double start = mdsecnd();

#pragma omp parallel num_threads(tds)
    {
        double ret = test_AVX(1.1,2.1,iterations);
        sum[omp_get_thread_num()] = ret;
    }

    double stop = mdsecnd();
    double secs = stop - start;

#ifdef ILP
    unsigned long long ops = 24 * 1000 * iterations * tds * 4;
#else
    unsigned long long ops = 48 * 1000 * iterations * tds * 4;
#endif

#ifdef ILP2
    ops = 16 * 1000 * iterations * tds * 4;
    //ops = 8 * 1000 * iterations * tds * 4;
#endif

    if (warmup == 0) {
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
    
    if (warmup == 0) {
    	cout << endl;
    }

    free(sum);
    return ((double) ops) / secs;
}

int main(int argc, const char* argv[]) {
    
	double start;
	
  	int sec = 0;
	int iters = 5;	
	int threads = 4;	

	if (argc >= 1) threads = atoi(argv[1]);
	if (argc >= 2) iters = atoi(argv[2]);
	if (argc >= 3) sec = atoi(argv[3]);


	if (sec != 0) {
        	//warmup	
		start = mdsecnd();
		while (mdsecnd() - start < sec ) {
			test_dp_mac_AVX(threads,2e6,1);
		}



		printf("warmup complete %f\n",mdsecnd() - start);
		socket_send("StartAVX\n");
		tsc_start();

        	//test	
		start = mdsecnd();
		while (mdsecnd() - start < sec ) {
			test_dp_mac_AVX(threads,2e6,1);
		}
		
		tsc_stop();
		socket_send("StopAVX");
		tsc_print();


        	//record performance	
		//double perf = test_dp_mac_AVX(threads,2e6,0);
		//tsc_printFileAll(perf / 1e9);
		
		

	} else {
		test_dp_mac_AVX(threads,iters * 1e6,0);
	}

	return 0;
}

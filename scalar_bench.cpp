#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>
#include <sys/time.h>
#include <omp.h>

#include <iostream>
using namespace std;

double test_dp_mac_SSE(double x,double y,size_t iterations){
    register __m128d r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,rA,rB,rC,rD,rE,rF;

    //  Generate starting data.
    r0 = _mm_set1_pd(x);
    r1 = _mm_set1_pd(y);

    r8 = _mm_set1_pd(-0.0);

    r2 = _mm_xor_pd(r0,r8);
    r3 = _mm_or_pd(r0,r8);
    r4 = _mm_andnot_pd(r8,r0);
    r5 = _mm_mul_pd(r1,_mm_set1_pd(0.37796447300922722721));
    r6 = _mm_mul_pd(r1,_mm_set1_pd(0.24253562503633297352));
    r7 = _mm_mul_pd(r1,_mm_set1_pd(4.1231056256176605498));
    r8 = _mm_add_pd(r0,_mm_set1_pd(0.37796447300922722721));
    r9 = _mm_add_pd(r1,_mm_set1_pd(0.24253562503633297352));
    rA = _mm_sub_pd(r0,_mm_set1_pd(4.1231056256176605498));
    rB = _mm_sub_pd(r1,_mm_set1_pd(4.1231056256176605498));

    rC = _mm_set1_pd(1.4142135623730950488);
    rD = _mm_set1_pd(1.7320508075688772935);
    rE = _mm_set1_pd(0.57735026918962576451);
    rF = _mm_set1_pd(0.70710678118654752440);

    unsigned long long iMASK = 0x800fffffffffffffull;
    __m128d MASK = _mm_set1_pd(*(double*)&iMASK);
    __m128d vONE = _mm_set1_pd(1.0);

    size_t c = 0;
    while (c < iterations){
        size_t i = 0;
        while (i < 1000){
            //  Here's the meat - the part that really matters.

            r0 = _mm_mul_sd(r0,rC);
            r1 = _mm_add_sd(r1,rD);
            r2 = _mm_mul_sd(r2,rE);
            r3 = _mm_sub_sd(r3,rF);
            r4 = _mm_mul_sd(r4,rC);
            r5 = _mm_add_sd(r5,rD);
            r6 = _mm_mul_sd(r6,rE);
            r7 = _mm_sub_sd(r7,rF);
            r8 = _mm_mul_sd(r8,rC);
            r9 = _mm_add_sd(r9,rD);
            rA = _mm_mul_sd(rA,rE);
            rB = _mm_sub_sd(rB,rF);

            r0 = _mm_add_sd(r0,rF);
            r1 = _mm_mul_sd(r1,rE);
            r2 = _mm_sub_sd(r2,rD);
            r3 = _mm_mul_sd(r3,rC);
            r4 = _mm_add_sd(r4,rF);
            r5 = _mm_mul_sd(r5,rE);
            r6 = _mm_sub_sd(r6,rD);
            r7 = _mm_mul_sd(r7,rC);
            r8 = _mm_add_sd(r8,rF);
            r9 = _mm_mul_sd(r9,rE);
            rA = _mm_sub_sd(rA,rD);
            rB = _mm_mul_sd(rB,rC);

            r0 = _mm_mul_sd(r0,rC);
            r1 = _mm_add_sd(r1,rD);
            r2 = _mm_mul_sd(r2,rE);
            r3 = _mm_sub_sd(r3,rF);
            r4 = _mm_mul_sd(r4,rC);
            r5 = _mm_add_sd(r5,rD);
            r6 = _mm_mul_sd(r6,rE);
            r7 = _mm_sub_sd(r7,rF);
            r8 = _mm_mul_sd(r8,rC);
            r9 = _mm_add_sd(r9,rD);
            rA = _mm_mul_sd(rA,rE);
            rB = _mm_sub_sd(rB,rF);

            r0 = _mm_add_sd(r0,rF);
            r1 = _mm_mul_sd(r1,rE);
            r2 = _mm_sub_sd(r2,rD);
            r3 = _mm_mul_sd(r3,rC);
            r4 = _mm_add_sd(r4,rF);
            r5 = _mm_mul_sd(r5,rE);
            r6 = _mm_sub_sd(r6,rD);
            r7 = _mm_mul_sd(r7,rC);
            r8 = _mm_add_sd(r8,rF);
            r9 = _mm_mul_sd(r9,rE);
            rA = _mm_sub_sd(rA,rD);
            rB = _mm_mul_sd(rB,rC);

            i++;
        }

        //  Need to renormalize to prevent denormal/overflow.
        r0 = _mm_and_pd(r0,MASK);
        r1 = _mm_and_pd(r1,MASK);
        r2 = _mm_and_pd(r2,MASK);
        r3 = _mm_and_pd(r3,MASK);
        r4 = _mm_and_pd(r4,MASK);
        r5 = _mm_and_pd(r5,MASK);
        r6 = _mm_and_pd(r6,MASK);
        r7 = _mm_and_pd(r7,MASK);
        r8 = _mm_and_pd(r8,MASK);
        r9 = _mm_and_pd(r9,MASK);
        rA = _mm_and_pd(rA,MASK);
        rB = _mm_and_pd(rB,MASK);
        r0 = _mm_or_pd(r0,vONE);
        r1 = _mm_or_pd(r1,vONE);
        r2 = _mm_or_pd(r2,vONE);
        r3 = _mm_or_pd(r3,vONE);
        r4 = _mm_or_pd(r4,vONE);
        r5 = _mm_or_pd(r5,vONE);
        r6 = _mm_or_pd(r6,vONE);
        r7 = _mm_or_pd(r7,vONE);
        r8 = _mm_or_pd(r8,vONE);
        r9 = _mm_or_pd(r9,vONE);
        rA = _mm_or_pd(rA,vONE);
        rB = _mm_or_pd(rB,vONE);

        c++;
    }

    r0 = _mm_add_pd(r0,r1);
    r2 = _mm_add_pd(r2,r3);
    r4 = _mm_add_pd(r4,r5);
    r6 = _mm_add_pd(r6,r7);
    r8 = _mm_add_pd(r8,r9);
    rA = _mm_add_pd(rA,rB);

    r0 = _mm_add_pd(r0,r2);
    r4 = _mm_add_pd(r4,r6);
    r8 = _mm_add_pd(r8,rA);

    r0 = _mm_add_pd(r0,r4);
    r0 = _mm_add_pd(r0,r8);

    //  Prevent Dead Code Elimination
    double out = 0;
    out += ((double*)&r0)[0];
    out += ((double*)&r0)[1];

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



void test_SSE(int tds,size_t iterations){

    double *sum = (double*)malloc(tds * sizeof(double));
    double start = mdsecnd();

#pragma omp parallel num_threads(tds)
    {
        double ret = test_dp_mac_SSE(1.1,2.1,iterations);
        sum[omp_get_thread_num()] = ret;
    }

    double stop = mdsecnd();
    double secs = stop - start;
    unsigned long long ops = 48 * 1000 * iterations * tds * 1;
    cout << "Seconds = " << secs << endl;
    cout << "FP Ops  = " << ops << endl;
    cout << "FLOPs   = " << ops / secs << endl;

    double out = 0;
    int c = 0;
    while (c < tds){
        out += sum[c++];
    }

    cout << "sum = " << out << endl;
    cout << endl;

    free(sum);
}

int main(int argc, const char* argv[]) {
	test_SSE(4,16e6);
	return 0;	
}

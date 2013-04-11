#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>
#include <sys/time.h>

#include <iostream>
using namespace std;

#ifdef __INTEL_COMPILER
inline __m256d operator + (const __m256d A, const __m256d B)
{
	    return _mm256_add_pd(A, B);
}

inline __m256d operator - (const __m256d A, const __m256d B)
{
	    return _mm256_sub_pd(A, B);
}

inline __m256d operator * (const __m256d A, const __m256d B)
{
	    return _mm256_mul_pd(A, B);
}
#endif

//
// Each iteration contains 48,000 instructions
//  x and y are used to seed the data
//
double avx_kernel(double x,double y,size_t iterations){
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


//#pragma GCC push_options
//#pragma GCC optimze("unroll-loops")
        size_t i = 0;
        while (i < 1000/UNROLLS) {

			//    - 48 Instructions per loop
			//    - 48*4 = 192 flops per loop

			/**
            r0 = ((((r0+rF) * rC) + rF) * rC); 
            r1 = ((((r1*rE) + rD) * rE) + rD);
            r2 = ((((r2-rD) * rE) - rD) * rE);
            r3 = ((((r3*rC) - rF) * rC) - rF);

		   	r4 = ((((r4+rF) * rC) + rF) * rC); 
            r5 = ((((r5*rE) + rD) * rE) + rD);
            r6 = ((((r6-rD) * rE) - rD) * rE);
            r7 = ((((r7*rC) - rF) * rC) - rF);

			r8 = ((((r8+rF) * rC) + rF) * rC); 
            r9 = ((((r9*rE) + rD) * rE) + rD);
            rA = ((((rA-rD) * rE) - rD) * rE);
            rB = ((((rB*rC) - rF) * rC) - rF);
           **/
			

			#include "avx_kernel_many.s"


            i++;
        }
//#pragma GCC pop_options



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

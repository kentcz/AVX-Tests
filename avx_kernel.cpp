#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>
#include <sys/time.h>
#include "init_array.h"

#ifdef USE_IACA
#include "/home/mic/iaca-lin32/include/iacaMarks.h"
#endif

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

	double *vals = (double *) _mm_malloc(16*4*sizeof(double),32);
	init_array(vals,64);

	//__declspec((align(32)) double constants[4] = {
	//	0.37796447300922722721,
	//};


	/**	
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
	**/

    unsigned long long iMASK = 0x800fffffffffffffull;
    __m256d MASK = _mm256_set1_pd(*(double*)&iMASK);
    __m256d vONE = _mm256_set1_pd(1.0);
	

	
	r0 = _mm256_load_pd(vals+0);
	r1 = _mm256_load_pd(vals+4);
	r2 = _mm256_load_pd(vals+8);
	r3 = _mm256_load_pd(vals+12);
	r4 = _mm256_load_pd(vals+16);
	r5 = _mm256_load_pd(vals+20);
	r6 = _mm256_load_pd(vals+24);
	r7 = _mm256_load_pd(vals+28);
	r8 = _mm256_load_pd(vals+32);
	r9 = _mm256_load_pd(vals+36);
	rA = _mm256_load_pd(vals+40);
	rB = _mm256_load_pd(vals+44);
	rC = _mm256_load_pd(vals+48);
	rD = _mm256_load_pd(vals+52);
	rE = _mm256_load_pd(vals+56);
	rF = _mm256_load_pd(vals+60);

	for (int w =0; w<64; w++) {
		printf("vals[%d]=%e\n", w , vals[w]);
	}


    size_t c = 0;
    while (c < iterations){

        size_t i = 0;
        while (i < 1000/UNROLLS) {

#ifdef USE_IACA
	IACA_START
#endif

			//    - 48 Instructions per loop
			//    - 48*4 = 192 flops per loop
			
			// Inlude the Kernel
			#include "kernel_include.cpp"
			

#ifdef USE_IACA
	IACA_END
#endif



            i++;
        }



		if (c==0) {
    		double out = ((double*)&r6)[0];
			printf("before r0=%e\n",out);
		}


		/**		
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
		**/

		if (c==100) {
    		double out = ((double*)&r6)[0];
			printf("after r0=%e\n",out);
		}
		

        c++;
    }

	_mm_free(vals);

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


    return out + x + y;
}

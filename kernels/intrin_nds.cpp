
			// 
            // This is the primary task
			//  each block contains 12 AVX instructions
			//    - 48 Instructions per loop
			//    - 48*4 = 192 flops per loop
			//
            r0 = _mm256_add_pd(r0,rF);
            r1 = _mm256_mul_pd(r1,rE);
            r2 = _mm256_sub_pd(r2,rD);
            r3 = _mm256_mul_pd(r3,rC);
            r4 = _mm256_add_pd(r4,rF);
            r5 = _mm256_mul_pd(r5,rE);
            r6 = _mm256_sub_pd(r6,rD);
            r7 = _mm256_mul_pd(r7,rC);
            r8 = _mm256_add_pd(r8,rF);
            r9 = _mm256_mul_pd(r9,rE);
            rA = _mm256_sub_pd(rA,rD);
            rB = _mm256_mul_pd(rB,rC);

            r0 = _mm256_mul_pd(r0,rC);
            r1 = _mm256_add_pd(r1,rD);
            r2 = _mm256_mul_pd(r2,rE);
            r3 = _mm256_sub_pd(r3,rF);
            r4 = _mm256_mul_pd(r4,rC);
            r5 = _mm256_add_pd(r5,rD);
            r6 = _mm256_mul_pd(r6,rE);
            r7 = _mm256_sub_pd(r7,rF);
            r8 = _mm256_mul_pd(r8,rC);
            r9 = _mm256_add_pd(r9,rD);
            rA = _mm256_mul_pd(rA,rE);
            rB = _mm256_sub_pd(rB,rF);

            r0 = _mm256_add_pd(r0,rF);
            r1 = _mm256_mul_pd(r1,rE);
            r2 = _mm256_sub_pd(r2,rD);
            r3 = _mm256_mul_pd(r3,rC);
            r4 = _mm256_add_pd(r4,rF);
            r5 = _mm256_mul_pd(r5,rE);
            r6 = _mm256_sub_pd(r6,rD);
            r7 = _mm256_mul_pd(r7,rC);
            r8 = _mm256_add_pd(r8,rF);
            r9 = _mm256_mul_pd(r9,rE);
            rA = _mm256_sub_pd(rA,rD);
            rB = _mm256_mul_pd(rB,rC);

            r0 = _mm256_mul_pd(r0,rC);
            r1 = _mm256_add_pd(r1,rD);
            r2 = _mm256_mul_pd(r2,rE);
            r3 = _mm256_sub_pd(r3,rF);
            r4 = _mm256_mul_pd(r4,rC);
            r5 = _mm256_add_pd(r5,rD);
            r6 = _mm256_mul_pd(r6,rE);
            r7 = _mm256_sub_pd(r7,rF);
            r8 = _mm256_mul_pd(r8,rC);
            r9 = _mm256_add_pd(r9,rD);
            rA = _mm256_mul_pd(rA,rE);
            rB = _mm256_sub_pd(rB,rF);



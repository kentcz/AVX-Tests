#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>
#include <math.h>

#include "simple_kernel.h"

#define LENGTH 64

void init_array(double *arr) {
	for (int i=0; i < LENGTH; i++) {
		arr[i] = (double) 1.0001 + (0.00001 * (4*atan(1.0)) * i);
	}
	//arr[0] = 4*atan((double)1);
}

void printVals(double *vals) {
	for (int i=0; i < LENGTH; i++) {
		printf("\tvals[%d]=%e\n", i, vals[i]);
	}
}


int main() {

	//__declspec((align(32)) double vals[64];
	double vals[64];
	
	init_array(vals);

	printf("Inputs:\n");
	printVals(vals);

	int ret = simple_kernel(vals,5e6);
	printf("ret=%d\n",ret);

	//ret = simple_kernel(vals,-3);
	//printf("ret=%d\n",ret);

	printf("Output:\n");
	printVals(vals);

	return 0;
}

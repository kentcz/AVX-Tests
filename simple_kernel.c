#include <stdio.h>

#define LENGTH 16

void simple_kernel(double *vals, int length) {

	int i;
	for (i=0; i < LENGTH; i++) {
		vals[i] = vals[i]+1;
	}
}

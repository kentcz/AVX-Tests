#include <math.h>

void init_array(double *arr, int len) {
	for (int i=0; i < len; i++) {
		arr[i] = (double) 1.0001 + (0.00001 * (4*atan(1.0)) * i);
	}
}

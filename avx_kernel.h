extern "C" int __cdecl avx_kernel(double *vals, int interations); 

//
// Each iteration contains 48,000 instructions
//  x and y are used to seed the data
//
//double avx_kernel(double x,double y,size_t iterations);

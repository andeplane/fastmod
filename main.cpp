/* 
	This example shows how it is much faster to use a&(b-1) than a%b if b=2^n and both numbers are unsigned integers.
	It is useful for e.g. array indices. Example:

	./main
	Finished using i%%N after 8.45381 seconds. Histogram for the first 10 values: 244141 244141 244141 244141 244141 244141 244141 244141 244141 244141

	Now using faster modulo operator
	Finished using i&NMinusOne after 0.570323 seconds. Histogram for the first 10 values: 244141 244141 244141 244141 244141 244141 244141 244141 244141 244141
*/
#include <iostream>
#include <ctime>

using namespace std;

int main(int args, char *argv[]) {
	unsigned long N = 4096; // Must be 2^N.
	unsigned long Nmax = 1e9;
	if(args>1) N = atoi(argv[1]); // If known compile time, the compiler will do this optimization automatically.
	unsigned long NminusOne = N-1;

	unsigned long values[N];
	memset(values, 0, N*sizeof(unsigned long)); // Set all values to zero

	clock_t beginTime = clock();
	for(unsigned long i=0; i<Nmax; i++) {
		values[i%N]++;
	}
	cout << "Finished using i%%N after " << double( clock () - beginTime ) / CLOCKS_PER_SEC << " seconds.";
	cout << " Histogram for the first 10 values: ";
	for(int i=0; i<10; i++) cout << values[i] << " ";
	cout << endl << endl << "Now using faster modulo operator" << endl;


	memset(values, 0, N*sizeof(unsigned long)); // Set all values to zero
	beginTime = clock();
	for(unsigned long i=0; i<Nmax; i++) {
		values[i&NminusOne]++;
	}
	cout << "Finished using i&NMinusOne after " << double( clock () - beginTime ) / CLOCKS_PER_SEC << " seconds.";
	cout << " Histogram for the first 10 values: ";
	for(int i=0; i<10; i++) cout << values[i] << " ";
	cout << endl;

	return 0;
}
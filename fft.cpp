/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include<iostream>
#include<complex>
#include<stdio.h>
#include<stdlib.h>
#include<cmath>
#define _USE_MATH_DEFINES

using namespace std;

typedef complex<double> dcomp;

int pow2(int n){
	if (n == 0) {
		return 1;
	}

	int pow = 2;
	while( n!=1 ) {
		n = n/2;
		pow *=2;
	}
	return pow;
}

// This filters an array into either the even or the odd values depending on the value of the flag
void filter(int bound, dcomp* input, dcomp* output_even, dcomp* output_odd){
	int i,k,j;
	for(i = 0, k = 0, j=0; i < bound; ++i) {
		if(i%2==0) {
			output_even[k] = input[i];
			++k;
		} else {
			output_odd[j] = input[i];
			++j;
		}
	}
}

// Evaluate the polynomial at n points
dcomp* evaluate(dcomp* A, int n, dcomp w){
	// Create an array to store the returned values
	dcomp* values = (dcomp*)malloc(n*sizeof(dcomp));

	if(n == 1) {
		values[0] = A[0];
	} else {
		int half_n = n/2;

		// Create an array to store the point value representation
		dcomp* A_even = values;
		dcomp* A_odd = values + half_n ;

		// Filter the values in A into A_even and A_odd
		filter(n, A, A_even, A_odd);

		// Recursively compute the values at n/2 points
		dcomp *V_even = evaluate(A_even, half_n, w*w);
		dcomp *V_odd = evaluate(A_odd, half_n, w*w);

		// Now compute the values at n points
		dcomp x=dcomp(1,0);
		for( int j = 0; j <half_n ; ++j) {
			values[j] = V_even[j] + x * V_odd[j];
			values[j + half_n] = V_even[j] - x * V_odd[j];
			x = x * w;
		}

		// delete the values obtained
		free(V_even);
		free(V_odd);
	}

	// return the computed values
	return values;
}

int main() {
	int test_cases;
	cin >> test_cases;

    // define the variables which will be required for computation
    dcomp A[2000];
    dcomp B[2000];
    dcomp C_eval[2000];
    dcomp *C, *A_eval, *B_eval;
    dcomp w;
	int i, j, k, n, lim, points;

    // Loop through all the test cases
	for(k = 0; k < test_cases; ++k) {
		cin >> n;

		// allocate memory for the two polynomials with the given degree
		points = pow2(2*n);

		// read the values
		for (j = 0; j <= n; ++j ) {
			cin >> A[j];
		}

		for (j = 0; j <= n; ++j ) {
			cin >> B[j];
		}

		// Extend the two input arrays to points number of points
		for (; j <points; ++j) {
			A[j] = 0;
			B[j] = 0;
		}

		// define omega
		w = polar(1.0, 2.0*M_PI/points);
		w = dcomp(w.real(), w.imag());
		A_eval = evaluate(A, points, w);
		B_eval = evaluate(B, points, w);

		// Compute the values of C on these points
		for(i = 0; i < points; i++ ) {
			C_eval[i] = A_eval[i] * B_eval[i];
		}

		C = evaluate(C_eval, points, dcomp(1.0,0)/w);

        // Compute the limits
		lim = 2 * n;
		for(i=0; i <= lim; i++){
			printf("%.0f ", C[i].real()/points);
		}
		cout << "\n";

		free(C);
        free(A_eval);
        free(B_eval);

	}
	return 0;
}

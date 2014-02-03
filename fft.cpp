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
#include<time.h>
#define SIZE 50000000

using namespace std;

#define PI 4 * atan(1)

// For ease of use, rename the complex template
typedef complex<double> dcomp;

// Global variables
dcomp* filter_temp;

long int pow2( long int n ){
	if ( n == 0 ) {
		return 1;
	}

	long int pow = 2;
	while( n != 1 ) {
		n /= 2;
		pow *= 2;
	}
	return pow;
}

// This filters an array into either the even or the odd values depending on the value of the flag
void filter( long int bound, dcomp* input ){
	long int i, k, j;
    long int half_bound = bound / 2;

	for( i = 0, k = 0, j = 0; i < bound; ++i ) {
		if( i % 2 == 0 ) {
            filter_temp[k] = input[i];
			++k;
		} else {
            filter_temp[half_bound + j] = input[i];
            ++j;
        }
	}

    for( i = 0; i < bound; ++i ) {
        input[i] = filter_temp[i];
    }
}

// Evaluate the polynomial at n points
dcomp* evaluate( dcomp* coeff_poly, long int n, dcomp w , dcomp* eval_poly ){
	if( n <= 1 ) {
		eval_poly[0] = coeff_poly[0];
	} else {
		long int half_n = n / 2;

		// Filter the values in A into A_even and A_odd
		filter( n, coeff_poly );

		// Recursively compute the values at n/2 points
        dcomp* even_eval = eval_poly;
        dcomp* odd_eval = ( eval_poly + half_n );
		evaluate( coeff_poly, half_n, w * w, even_eval );
		evaluate((coeff_poly + half_n), half_n, w * w, odd_eval );

		// Now compute the values at n points
		dcomp x = 1;
        dcomp val_even, val_odd;
        dcomp val1, val2;
		for( long int j = 0; j <half_n ; ++j ) {
            val_even = even_eval[j];
            val_odd = x * odd_eval[j];
			eval_poly[j] = val_even + val_odd;
			eval_poly[j + half_n] = val_even - val_odd;
			x = x * w;
		}
	}

	// return the computed values
    return eval_poly;
}

int main() {
    // define the variables which will be required for computation
    clock_t t1, t2;
	long int i, j, k, n, max_degree, upper_bound, test_cases;
    dcomp w;
    dcomp* pol1 = new dcomp[SIZE];
    dcomp* pol2 = new dcomp[SIZE];
    filter_temp = new dcomp[SIZE];

    // Loop through all the test cases
	cin >> test_cases;
    t1 = clock();
	for( k = 0; k < test_cases; ++k ) {
		cin >> n;

		// allocate memory for the two polynomials with the given degree
		upper_bound= pow2( 2 * n );

		// read the values
		for (j = 0; j <= n; ++j ) {
			cin >> pol1[j];
		}

		for (j = 0; j <= n; ++j ) {
			cin >> pol2[j];
		}

		// Extend the two input arrays to points number of points
		for ( ; j <= upper_bound; ++j ) {
			pol1[j] = 0;
			pol2[j] = 0;
		}

		// define omega
		w = polar( 1.0, 2.0 * PI / upper_bound );
		evaluate( pol1, upper_bound, w , pol1 );
		evaluate( pol2, upper_bound, w , pol2 );

		// Compute the values of C on these points
		for( i = 0; i <= upper_bound; i++ ) {
			pol2[i] = pol1[i] * pol2[i];
		}

        // Now interpolate the polynomial
		evaluate( pol2, upper_bound, dcomp( 1.0, 0) / w , pol1 );

        // Compute the limits
		max_degree = 2 * n;
		for( i = 0; i <= max_degree; i++ ){
            // printf("%.0lf ", pol1[i].real() / upper_bound);
		}
        // cout << endl;
	}

    t2 = clock();
    cout << (float)(t2-t1)/(test_cases * CLOCKS_PER_SEC) << endl;

	return 0;
}

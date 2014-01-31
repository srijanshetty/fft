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
#include<deque>
#define _USE_MATH_DEFINES

using namespace std;

// For ease of use
typedef complex<double> dcomp;
typedef deque<dcomp> comp_queue;

// To computer the nearest power of 2
long power_2( long n ){
	if ( n == 0 ) {
		return 1;
	}

	long pow = 2;
	while( n != 1 ) {
		n /= 2;
		pow *= 2;
	}
	return pow;
}

// This filters an array into either the even or the odd values depending on the value of the flag
void filter( comp_queue &input, comp_queue &even, comp_queue &odd ){
    int i = 0;
    comp_queue::iterator iter;

    // Filter the input to create two arrays storing the even and the
    // odd coefficients
    for( iter = input.begin(); iter != input.end(); ++iter, ++i ) {
        if( i % 2 == 0 ) {
            even.push_back( *iter );
        } else {
            odd.push_back( *iter );
        }
    }

    // Clear out the input
    input.clear();
}

// Evaluate the polynomial at n points
comp_queue evaluate( comp_queue &poly, dcomp root ) {
    int size = poly.size();
    comp_queue result(size);

    /*
    // In the base case the value is the value of the constant term
    if( size == 1 ) {
        result.push_back( poly.back() );
    } else {
        comp_queue even, odd, even_eval, odd_eval;

        // First we filter A into it's even and odd componenets
        // Then evaluate recursively the even part and the odd part
        filter( poly, even, odd );
        even_eval = evaluate( even, root * root );
        odd_eval = evaluate( odd, root * root );

		// Now compute the values at n points
		dcomp temp = 1;
        int j, half_size;
		for( j = 0; j < half_size ; ++j ) {
			result[j] = even_eval[j] + temp * odd_eval[j];
			result[j + half_size] = odd_eval[j] - temp * odd_eval[j];
			temp = temp * root;
		}

        // clear out the residual stuff
        even_eval.clear();
        odd_eval.clear();
    }
    */

    // return the result to the calling function
    return result;
}

int main() {
	int test_cases, k, degree, result_degree, upper_bound, i, j;
    comp_queue first, second, result, first_eval, second_eval, result_eval;
    dcomp temp, w;

    // Loop through all the test cases
	cin >> test_cases;
	for(k = 0; k < test_cases; ++k) {
		cin >> degree;

		// allocate memory for the two polynomials with the given degree
		upper_bound = power_2( 2 * degree );

		// read the values
		for ( j = 0; j <= degree; ++j ) {
            cin >> temp;
            first.push_back( temp );
		}

		for ( j = 0; j <= degree; ++j ) {
            cin >> temp;
            second.push_back( temp );
		}
        
		// Extend the two input arrays to points number of points
		for ( ; j <= upper_bound; ++j ) {
            first.push_back( 0 );
            second.push_back( 0 );
		}

		// define omega
		w = polar( 1.0, 2.0*M_PI/upper_bound);
		w = dcomp( w.real(), w.imag() );
        /*
		first_eval = evaluate( first, w );
		second_eval = evaluate( second, w );

		// Compute the values of C on these points
		for( i = 0; i <= upper_bound; i++ ) {
			result_eval[i] = first_eval[i] * second_eval[i];
		}

		result = evaluate( result_eval, dcomp(1.0,0) / w );

        // Compute the limits
		result_degree = 2 * degree;
		for(i=0; i <= result_degree; i++){
			printf("%.0f ", result[i].real()/upper_bound);
		}
		cout << endl;
        */
        evaluate(first, w);
	}

    return 0;
}

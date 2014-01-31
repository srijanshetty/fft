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
long power_2(long n){
	if (n == 0) {
		return 1;
	}

	long pow = 2;
	while( n!=1 ) {
		n /= 2;
		pow *=2;
	}
	return pow;
}

// This filters an array into either the even or the odd values depending on the value of the flag
void filter(comp_queue &input, comp_queue &even, comp_queue &odd){
    int i = 0;
    comp_queue::iterator iter;

    // Filter the input to create two arrays storing the even and the
    // odd coefficients
    for(iter = input.begin(); iter != input.end(); ++iter, ++i ) {
        if( i % 2 == 0 ) {
            even.push_back( *iter );
        } else {
            odd.push_back( *iter );
        }
    }
}

/*
// Evaluate the polynomial at n points
comp_queue evaluate(comp_queue &poly, comp_queue &result){
    int size = input.size();

    // In the base case the value is the value of the constant term
    if( size == 1 ) {
        result.push_back(poly.back());
    } else {
        // First we filter A into it's even and odd componenets
        dcomp even, odd;
        filter(poly, even, odd);
        poly.clear(); // we won't be needing the polynomial anymore

        // Evaluate recursively the even part and the odd part
        evaluate(even, even_eval, root * root);
        evaluate(odd, odd_eval, root * root);

        // clear out the residual information
        even.clear();
        odd.clear();
        
		// Now compute the values at n points
		dcomp temp = 1;
		for( int j = 0; j <half_n ; ++j) {
			result[j] = even_eval[j] + temp * odd_eval[j];
			result[j + half_n] = odd_eval[j] - temp * odd_eval[j];
			temp = temp * w;
		}
    }
}
*/

int main() {
    comp_queue first, second, result;
    comp_queue even, odd;
    first.push_back(0);
    first.push_back(1);
    first.push_back(2);
    first.push_back(3);
    first.push_back(4);
    first.push_back(5);

    filter(first, even, odd);
    first.clear();
    comp_queue::iterator iter;
    for(iter = even.begin(); iter != even.end(); ++iter ) {
        cout << *iter << " ";
    }
    cout << endl;

    for(iter = odd.begin(); iter != odd.end(); ++iter ) {
        cout << *iter << " ";
    }
    cout << endl;

    for(iter = first.begin(); iter != first.end(); ++iter ) {
        cout << *iter << " ";
    }
    cout << endl;

    return 0;
}


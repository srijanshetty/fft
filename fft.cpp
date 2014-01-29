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

#define _USE_MATH_DEFINES
#include<iostream>
#include<complex>
#include<stdlib.h>
#include<cmath>

using namespace std;

typedef complex<double> dcomp;

int pow2(int n){
    if (n == 0) {
        return 1;
    }

    int pow = 2;
    while( n!=1 ) {
        n = n/2;
        pow *= 2;
    }
    return pow;
}

// This filters an array into either the even or the odd values depending on the value of the flag
void filter(int flag, int bound, dcomp* input, dcomp* output){
    int i,k;
    for(i = flag, k = 0; i < bound; i+=2, k++) {
        output[k] = input[i];
    }
}

// Evaluate the polynomial at n points
dcomp* evaluate(dcomp* A, int n){
    // Create an array to store the returned values
    dcomp* values = (dcomp*)malloc(n*sizeof(dcomp));

    if(n == 1) {
        values[0] = A[0];
    } else {
        int half_n = n/2;

        // Create an array to store the point value representation
        dcomp* A_even = values;
        dcomp* A_odd = values + half_n;

        // Filter the values in A into A_even and A_odd
        filter(0, n, A, A_even);
        filter(1, n, A, A_odd);

        // Recursively compute the values at n/2 points
        dcomp *V_even = evaluate(A_even, half_n);
        dcomp *V_odd = evaluate(A_odd, half_n);

        // define omega
        dcomp w = polar(1.0, 2.0*M_PI/n);
        cout << n << ":::::::::" << arg(w) << "\n";
        dcomp temp;

        // Now compute the values at n points
        for( int j = 0; j < half_n ; ++j) {
            temp = w * V_odd[j];
            values[j] = V_even[j] + temp;
            values[j + half_n] = V_even[j] - temp;
            w *= w;
        }

        // delete the values obtained
        delete V_even;
        delete V_odd;
    }

    // return the computed values
    return values;
}

int main() {
    int n;
    cin >> n;

    // allocate memory for the two polynomials with the given degree
    int points = pow2(2*n);
    dcomp* A = (dcomp*)malloc(points*sizeof(dcomp));
    dcomp* B = (dcomp*)malloc(points*sizeof(dcomp));
    dcomp* C_eval = (dcomp*)malloc(points*sizeof(dcomp));

    // read the values
    int i,j;
    for (j = 0; j <= n; ++j ) {
        cin >> A[j];
    }

    for (j = 0; j <= n; ++j ) {
        cin >> B[j];
    }

    // Extend the two input arrays to points number of points
    for (; j < points; ++j) {
        A[j] = 0;
        B[j] = 0;
    }

    dcomp *A_eval = evaluate(A, points);
    dcomp *B_eval = evaluate(B, points);

    // Compute the values of C on these points
    for(i = 0; i < points; i++ ) {
        C_eval[i] = A_eval[i] * B_eval[i];
    }

    dcomp* C = (dcomp*)malloc(points*sizeof(dcomp));
    C = evaluate(C_eval, points);

    for(i = 0 ; i < points; i++ ){
        C_eval[i] = C[points-i]/dcomp(points, 0);
    }

    for(i=0;i<points;i++){
        cout << C_eval[i] << "\n";
    }
}


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
#include<stdlib.h>
#include<time.h>
#define SIZE 10000000

using namespace std;

int main() {
    clock_t t1,t2;
    long int i, j, k, degree, result_degree, test_cases, temp;
    long int* A = new long int[SIZE];
    long int* B = new long int[SIZE];
    long int* C = new long int[SIZE];

    // read the values
    cin >> test_cases;
    t1 = clock();
    for( i = 0; i < test_cases; ++i) {
        cin >> degree;
        result_degree = 2 * degree;

        for (j = 0; j <= degree; ++j ) {
            cin >> A[j];
        }

        for (j = 0; j <= degree; ++j ) {
            cin >> B[j];
        }

        for( j = 0; j <= result_degree; ++j ) {
            temp = 0;

            if( j <= degree ) {
                for ( k = 0; k <= j; ++k ) {
                    temp += A[k] * B[j - k];
                }
            } else {
                for( k = ( j - degree ); k <= degree; ++k ) {
                    temp += A[k] * B[degree - ( k - ( j - degree ) )];
                }
            }

            C[j] = temp;
        }

        for( j = 0; j <= result_degree; ++j ) {
            // cout<< C[j] << " ";
        }
        // cout << endl;
    }

    t2 = clock();
    cout << (float)(t2-t1)/(test_cases * CLOCKS_PER_SEC) << endl;
    return 0;
}

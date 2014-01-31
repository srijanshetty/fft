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

using namespace std;

int main() {
    int i, j, k, degree, result_degree, test_cases;
    long A[2000], B[2000], C[2000];

    // read the values
    cin >> test_cases;
    for( i = 0; i < test_cases; ++i) {
        cin >> degree;
        result_degree = 2 * degree;

        for (j = 0; j <= degree; ++j ) {
            cin >> A[j];
        }

        for (j = 0; j <= degree; ++j ) {
            cin >> B[j];
        }

        for (j = (degree + 1); j <= result_degree; ++j ) {
            A[j] = 0;
            B[j] = 0;
        }

        for( j = 0; j <= result_degree; ++j ) {
            C[j] = 0;

            for ( k = 0; k <= j; ++k ) {
                C[j] += A[k] * B[j - k];
            }
        }

        for( j = 0; j <= max_degree; ++j ) {
            cout<< C[j] << " ";
        }
        cout << endl;
    }
    return 0;
}

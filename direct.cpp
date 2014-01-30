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
    int test_cases;
    cin >> test_cases;

    int A[2000], B[2000], C[2000];

    // read the values
    int i, j, k, n, points, temp;
    for( i = 0; i < test_cases; ++i) {
        cin >> n;

        for (j = 0; j <= n; ++j ) {
            cin >> A[j];
        }

        for (j = 0; j <= n; ++j ) {
            cin >> B[j];
        }

        points = 2*n;
        for (; j <= points; ++j ) {
            A[j] = 0;
            B[j] = 0;
        }

        temp;
        for(j = 0; j <= points; ++j ) {
            temp = 0;
            for (k = 0; k <=j; ++k ) {
                temp += A[k] * B[j-k];
            }
            C[j] = temp;
            cout<< C[j] << " ";
        }
        cout<< "\n";
    }
    return 0;
}

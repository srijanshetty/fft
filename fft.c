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

#include<stdio.h>
#include<malloc.h>

int pow2(int n){
    int pow = 2;
    while( n!=1 ) {
        n = n/2;
        pow *=2;
    }
    return pow;
}

void filter(int val, int* input, int* output, int bound){
    int i,k;
    for(i = val, k = 0; i < bound; i+=2, k++) {
        output[k] = input[i];
    }
}

int evaluate(int* A, int n){
    if (n == 1){
    } else {
        int* V = (int*)malloc(2*n*sizeof(int));
        int* A_even = V;
        int* A_odd = (V+(n-1));
        filter(1, A_even, A, n);
        filter(0, A_odd, A, n);
    }
    return 0;

}
        

int main() {
    int A[10] = {0,1,2,3,4,5,6,7,8,9};
    int B[5];
    filter(1, A, B, 10);
    int i;
    for(i = 0; i < 5; ++i) {
        printf("%d", B[i]);
    }
    return 1;
}


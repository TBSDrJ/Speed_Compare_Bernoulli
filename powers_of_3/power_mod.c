#include<stdio.h>

long binary_places(long n) {
    long i;
    for (i=1; i<64; i++) {
        if ((n >> i) == 0) {
            break;
        }
    }
    return i;
}

long power_mod(long n, long k, long p) {
    long result = n;
    long bin_pl, i;
    bin_pl = binary_places(n);
    for (i=1; i<k; i++) {
        if (result >> (64 - bin_pl - 1) == 0) {
            result *= n;
        } else {
            result %= p;
            result *= n;
        }
    }
    return result % p;
}

int main() {
    long n = 0;
    for (int k=0; k<1000; k++) {
        for (int i=1; i<100; i++) {
            for (int j=1; j<100; j++) {
                n = power_mod(3, j, 103);
                // printf("%3li  ", n*i % 103);
                // if (j % 10 == 0) {
                //     printf("\n");
                // }
            }
            // printf("\n");
        }
        // printf("\n");
    }
}
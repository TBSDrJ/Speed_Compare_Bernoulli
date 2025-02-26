#include<stdio.h>

long powers_3[32] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void fill_powers() {
    for (int i=1; i<32; i++) {
        powers_3[i] = powers_3[i-1] * 3;
    }
}

long trits_to_dec (long trits) {
    long total = 0, trit;
    for (int i=0; i<32; i++) {
        trit = trits & 3;
        total += powers_3[i] * trit;
        // printf("%li %li %li %li\n", trits, trit, total, powers_3[i]);
        trits >>= 2;
    }
    return total;
}

long dec_to_trits (long dec) {
    long trits = 0;
    for (int i=31; i>=0; i--) {
        while (powers_3[i] <= dec) {
            dec -= powers_3[i];
            trits += 1 << i << i;
        }
    }
    return trits;
}

long power_mod_shift(long n, long k, long p) {
    long trits = dec_to_trits(n);
    long result;
    for (int i=1; i<k; i++) {
        if ((trits & ((long) 3 << 62)) == 0) {
            trits <<= 2;
        } else {
            trits = dec_to_trits(trits_to_dec(trits) % p);
            trits <<= 2;
        }
    }
    result = trits_to_dec(trits);
    result %= p;
    return result;
}

int main() {
    long trits = 1, n = 0;
    fill_powers();
    for (int k=0; k<1000; k++) {
        for (int i=1; i<100; i++) {
            for (int j=1; j<100; j++) {
                n = power_mod_shift(i, j, 103);
                // printf("%3li  ", n);
                // if (j % 10 == 0) {
                //     printf("\n");
                // }
            }
            // printf("\n");
        }
        // printf("\n");
    }
}
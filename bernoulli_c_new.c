#include<stdio.h>
#include<math.h>
#include<stdbool.h>
#include<stdlib.h>

const long max_prime = 2000;
const long num_primes = 300;

// Calculates all primes up to max_prime (const set above)
void calc_primes(long primes[]) {
    long i, j;
    bool sieve[max_prime];
    sieve[0] = 0;
    sieve[1] = 0;
    for (i=2; i<max_prime; i++) {sieve[i] = 1;}
    for (i=2; i<max_prime; i++) {
        if (sieve[i] == 1) {
            for (j=2*i; j<max_prime; j+=i) {
                sieve[j] = 0; 
            }
        }
    }
    // We want to skip the first few primes
    sieve[2] = 0;
    sieve[3] = 0;
    sieve[5] = 0;
    sieve[7] = 0;
    j = 0;
    for (i=0; i<max_prime; i++) {
        if (sieve[i] == 1) {
            primes[j] = i;
            j++;
        }
    }
}

// calculates the number of nonzero binary digits for n.
// Value is equal to the floor(log2(n)) + 1, but this is faster.
// This helps calculate n^k (mod p) for large values of n^k
// I tried the function __builtin_clz which does basically the same thing
//    but it slowed down the program a lot (e.g. 1.6s -> over 4s)
// In Fortran, much faster to use the builtin.
long binary_places(long n) {
    long i;
    for (i=1; i<64; i++) {
        if ((n >> i) == 0) {
            break;
        }
    }
    return i;
}

// Calculates n^k (mod p) even when n^k is much larger than the data type holds.
// Assumes n < p.
long power_mod(long n, long k, long p) {
    long running = n, result = 1;
    long i, bin_pl_k;
    bin_pl_k = binary_places(k);
    long* results = (long*) malloc(bin_pl_k * sizeof(long));
    results[0] = n;
    for (i=1; i<bin_pl_k; i++) {
        running %= p;
        running *= running;
        results[i] = running;
    }
    for (i=0; i<bin_pl_k; i++) {
        if (k >> (i+1) << (i+1) != k >> i << i) {
            result *= results[i];
            result %= p;
        }
    }
    free(results);
    return result % p;
}

// Calculates 2^k (mod p) using bit shifting.
long power_2_mod(long k, long p) {
    long result = 2, i;
    for (i=1; i<k; i++) {
        if (result >> 61 == 0) {
            result = result << 1;
        } else {
            result %= p;
            result = result << 1;
        }
    }
    return result % p;
}

// Calculates the 3 powers part of Vandiver's Theorem 1
// Notice that k here matches 2k in Bernoulli.md
long three_powers_1(long p, long k, long* power_2, long* power_3) {
    long result;  
    *power_2 = power_2_mod(p-2*k, p);
    *power_3 = power_mod(3, p-2*k, p);
    result = *power_2 + *power_3 - (*power_2)*(*power_2) - 1;
    while (result < 0) {result += p;}
    while (result >= p) {result -= p;}
    return result;
}

// Calculates the 3 powers part of Vandiver's Theorem 2
long three_powers_2(long p, long k, long* power_2, long* power_3) {
    long result;  
    result = (*power_2)*(*power_2);
    result += (*power_3);
    result -= (*power_2)*(*power_3);
    result -= 1;
    while (result < 0) {result += p;}
    while (result >= p) {result -= p;}
    return result;
}

// Calculates the 3 powers part of Vandiver's Theorem 3
long three_powers_3(long p, long k, long* power_2, long* power_3) {
    long result;  
    result = (*power_2)*(*power_2);
    result += power_mod(5, p-2*k, p); 
    result -= (*power_2)*(*power_2)*(*power_2);
    result -= 1; 
    while (result < 0) {result += p;}
    while (result >= p) {result -= p;}
    return result;
}

// Calculates the left side of Vandiver's Theorem 4 even though it's not
// a sum of three powers, I'm still calling it 3 powers
long three_powers_4(long p, long k) {
    long result;  
    result = power_2_mod(2*k-1, pow(p,3));
    result *= p;
    while (result < 0) {result += pow(p,3);}
    while (result >= pow(p,3)) {result -= pow(p,3);}
    return result;
}

// Calculates the sum part of Vandiver's Theorem 1
long sum_1(long p, long k) {
    long begin = ceil((double) p / 4.0);
    long end = ceil((double) p / 3.0);
    long j, result = 0;
    for (j = begin; j < end; j++) {
        result += power_mod(j, 2*k - 1, p);
    }
    while (result < 0) {result += p;}
    while (result >= p) {result -= p;}
    return result;
}

// Calculates the sum part of Vandiver's Theorem 2
long sum_2(long p, long k) {
    long begin = ceil((double) p / 6.0);
    long end = ceil((double) p / 4.0);
    long j, result = 0;
    for (j = begin; j < end; j++) {
        result += power_mod(j, 2*k - 1, p);
    }
    while (result < 0) {result += p;}
    while (result >= p) {result -= p;}
    return result;
}

// Calculates the sum part of Vandiver's Theorem 3
long sum_3(long p, long k) {
    long begin = ceil((double) p / 8.0);
    long end = ceil((double) p / 5.0);
    long j, result = 0;
    for (j = begin; j < end; j++) {
        result += power_mod(j, 2*k - 1, p);
    }
    begin = ceil((double) 3*p / 8.0);
    end = ceil((double) 2*p / 5.0);
    for (j = begin; j < end; j++) {
        result += power_mod(j, 2*k - 1, p);
    }
    while (result < 0) {result += p;}
    while (result >= p) {result -= p;}
    return result;
}

// Calculates the sum part of Vandiver's Theorem 4
long sum_4(long p, long k) {
    long begin = 1;
    long end = (float) ((p-1)/2);
    long j, result = 0;
    for (j = begin; j < end; j++) {
        result += power_mod(p-2*j, 2*k, pow(p,3));
    }
    while (result < 0) {result += pow(p,3);}
    while (result >= pow(p,3)) {result -= pow(p,3);}
    return result;
}

int main() {
    long i, p, k, t_1, t_2, t_3, t_4, s_1, s_2, s_3, s_4;
    long* power_2 = (long*) malloc(sizeof(long));
    long* power_3 = (long*) malloc(sizeof(long));
    long primes[num_primes] = {};
    bool go_t_2 = false, go_t_3 = false, go_t_4 = false;
    long t_2_reached = 0, t_3_reached = 0, t_4_reached= 0;
    calc_primes(primes);
    for (i=0; i<num_primes; i++) {
        p = primes[i];
        if (p == 0) {break;}
        for (k=3; k<=(p-3)/2; k++) {
            t_1 = three_powers_1(p, k, power_2, power_3);
            if (t_1 == 0) {
                // test 1 is inconclusive
                go_t_2 = true;
                t_2_reached++;
            }
            else {
                s_1 = sum_1(p, k);
                if (s_1 == 0) {
                    printf("t1: %li %li\n", p, 2*k);
                }
            }
            if (go_t_2) {
                go_t_2 = false;
                t_2 = three_powers_2(p, k, power_2, power_3);
                if (t_2 == 0) {
                    // test 2 is inconclusive
                    go_t_3 = true;
                    t_3_reached++;
                }
                else {
                    s_2 = sum_2(p, k);
                    if (s_2 == 0) {
                        printf("t2: %li %li\n", p, 2*k);
                    }
                }
            }
            if (go_t_3) {
                go_t_3 = false;
                t_3 = three_powers_3(p, k, power_2, power_3);
                if (t_3 == 0) {
                    // test 3 is inconclusive
                    go_t_4 = true;
                    t_4_reached++;
                }
                else {
                    s_3 = sum_3(p, k);
                    if (s_3 == 0) {
                        printf("t3: %li %li\n", p, 2*k);
                    }
                }
            }
            if (go_t_4) {
                go_t_4 = false;
                if (2*k % (p-1) == 2) {
                    printf("Inconclusive: %li %li", p, 2*k);
                }
                t_4 = three_powers_4(p, k);
                if (t_4 == 0) {
                    printf("Inconclusive: %li %li", p, 2*k);
                } else {
                    s_4 = sum_4(p, k);
                    if (s_4 == 0) {
                        printf("t4: %li %li\n", p, 2*k);
                    }
                }
            }
        }
    }
    free(power_2);
    free(power_3);
    printf("test2: %li test3: %li test4: %li\n", t_2_reached, t_3_reached, t_4_reached);
}
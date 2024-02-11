#include<stdio.h>
#include<math.h>
#include<stdbool.h>

const int max_prime = 1000;
const int num_primes = 168;

// Calculates all primes up to max_prime (const set above)
void calc_primes(int primes[]) {
    int i, j;
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
int binary_places(int n) {
    int i;
    for (i=1; i<32; i++) {
        if ((n >> i) == 0) {
            break;
        }
    }
    return i;
}

// Calculates n^k (mod p) even when n^k is much larger than the data type holds.
// Assumes n < p.
int power_mod(int n, int k, int p) {
    int result = n;
    int bin_pl, i;
    bin_pl = binary_places(n);
    for (i=1; i<k; i++) {
        if (result >> (32 - bin_pl - 1) == 0) {
            result *= n;
        } else {
            result %= p;
            result *= n;
        }
    }
    return result % p;
}

// Calculates 2^k (mod p) using bit shifting.
int power_2_mod(int k, int p) {
    int result = 2, i;
    for (i=1; i<k; i++) {
        if (result >> 30 == 0) {
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
int three_powers_1(int p, int k) {
    int result;  
    result = power_2_mod(p-2*k, p);
    result += power_mod(3, p-2*k, p);
    result -= power_2_mod(2*p-4*k, p);
    result -= 1;
    while (result < 0) {result += p;}
    while (result >= p) {result -= p;}
    return result;
}

// Calculates the 3 powers part of Vandiver's Theorem 2
int three_powers_2(int p, int k) {
    int result;  
    result = power_2_mod(2*p-4*k, p);;
    result += power_mod(3, p-2*k, p);
    result -= power_mod(6, p-2*k, p);
    result -= 1;
    while (result < 0) {result += p;}
    while (result >= p) {result -= p;}
    return result;
}

// Calculates the 3 powers part of Vandiver's Theorem 3
int three_powers_3(int p, int k) {
    int result;  
    result = power_2_mod(2*p-4*k, p);;
    result += power_mod(5, p-2*k, p);
    result -= power_2_mod(3*p-6*k, p);
    result -= 1;
    while (result < 0) {result += p;}
    while (result >= p) {result -= p;}
    return result;
}

// Calculates the left side of Vandiver's Theorem 4 even though it's not
// a sum of three powers, I'm still calling it 3 powers
int three_powers_4(int p, int k) {
    int result;  
    result = power_2_mod(2*k-1, pow(p,3));
    result *= p;
    while (result < 0) {result += pow(p,3);}
    while (result >= pow(p,3)) {result -= pow(p,3);}
    return result;
}

// Calculates the sum part of Vandiver's Theorem 1
int sum_1(int p, int k) {
    int begin = ceil((double) p / 4.0);
    int end = ceil((double) p / 3.0);
    int j, result = 0;
    for (j = begin; j < end; j++) {
        result += power_mod(j, 2*k - 1, p);
    }
    while (result < 0) {result += p;}
    while (result >= p) {result -= p;}
    return result;
}

// Calculates the sum part of Vandiver's Theorem 2
int sum_2(int p, int k) {
    int begin = ceil((double) p / 6.0);
    int end = ceil((double) p / 4.0);
    int j, result = 0;
    for (j = begin; j < end; j++) {
        result += power_mod(j, 2*k - 1, p);
    }
    while (result < 0) {result += p;}
    while (result >= p) {result -= p;}
    return result;
}

// Calculates the sum part of Vandiver's Theorem 3
int sum_3(int p, int k) {
    int begin = ceil((double) p / 8.0);
    int end = ceil((double) p / 5.0);
    int j, result = 0;
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

// Calculates the sum part of Vandiver's Theorem 2
int sum_4(int p, int k) {
    int begin = 1;
    int end = (float) ((p-1)/2);
    int j, result = 0;
    for (j = begin; j < end; j++) {
        result += power_mod(p-2*j, 2*k, pow(p,3));
    }
    while (result < 0) {result += pow(p,3);}
    while (result >= pow(p,3)) {result -= pow(p,3);}
    return result;
}

int main() {
    int i, p, k, t_1, t_2, t_3, t_4, s_1, s_2, s_3, s_4;
    int primes[num_primes] = {};
    bool go_t_2 = false, go_t_3 = false, go_t_4 = false;
    int t_2_reached = 0, t_3_reached = 0, t_4_reached= 0;
    calc_primes(primes);
    for (i=0; i<num_primes; i++) {
        p = primes[i];
        if (p == 0) {break;}
        for (k=3; k<=(p-3)/2; k++) {
            t_1 = three_powers_1(p, k);
            if (t_1 == 0) {
                // test 1 is inconclusive
                go_t_2 = true;
                t_2_reached++;
            }
            else {
                s_1 = sum_1(p, k);
                if (s_1 == 0) {
                    printf("t1: %i %i\n", p, 2*k);
                }
            }
            if (go_t_2) {
                go_t_2 = false;
                t_2 = three_powers_2(p, k);
                if (t_2 == 0) {
                    // test 2 is inconclusive
                    go_t_3 = true;
                    t_3_reached++;
                }
                else {
                    s_2 = sum_2(p, k);
                    if (s_2 == 0) {
                        printf("t2: %i %i\n", p, 2*k);
                    }
                }
            }
            if (go_t_3) {
                go_t_3 = false;
                t_3 = three_powers_3(p, k);
                if (t_3 == 0) {
                    // test 3 is inconclusive
                    go_t_4 = true;
                    t_4_reached++;
                }
                else {
                    s_3 = sum_3(p, k);
                    if (s_3 == 0) {
                        printf("t3: %i %i\n", p, 2*k);
                    }
                }
            }
            if (go_t_4) {
                go_t_4 = false;
                if (2*k % (p-1) == 2) {
                    printf("Inconclusive: %i %i", p, 2*k);
                }
                t_4 = three_powers_4(p, k);
                if (t_4 == 0) {
                    printf("Inconclusive: %i %i", p, 2*k);
                } else {
                    s_4 = sum_4(p, k);
                    if (s_4 == 0) {
                        printf("t4: %i %i\n", p, 2*k);
                    }
                }
            }
        }
    }
    printf("test2: %i test3: %i test4: %i\n", t_2_reached, t_3_reached, t_4_reached);
}
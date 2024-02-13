import java.lang.Math;
import java.util.Arrays;

public class Bernoulli {
    static final int max_prime = 1000;
    static final int num_primes = 200;

    static public long[] calc_primes() {
        long [] sieve = new long[max_prime];
        long [] primes = new long[num_primes];
        int i = 0, j = 0;
        long n = 0;
        Arrays.fill(sieve, 1);
        sieve[0] = 0;
        sieve[1] = 0;
        for (i=2; i<max_prime; i++) {
            if (sieve[i] == 1) {
                for (j=2*i; j<max_prime; j+=i) {
                    sieve[j] = 0;
                }
            }
        }
        sieve[2] = 0;
        sieve[3] = 0;
        sieve[5] = 0;
        sieve[7] = 0;
        j = 0;
        for (i=0; i<max_prime; i++) {
            if ((sieve[i] == 1) && (j < 200)) {
                primes[j] = i;
                j++;
            }
        }
        return primes;
    }

    static public long binary_places(long n) {
        int i = 0;
        for (i=0; i<64; i++) {
            if (n >> i == 0) {
                break;
            }
        }
        return i;
    }

    static public long power_mod(long n, long k, long p) {
        long i = 0;
        long result = n;
        long bin_pl = Bernoulli.binary_places(n);
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

    static public long power_2_mod(long k, long p) {
        long i = 0;
        long result = 2;
        for (i=1; i<k; i++) {
            if (result >> 62 == 0) {
                result = result << 1;
            } else {
                result %= p;
                result = result << 1;
            }
        }
        return result % p;
    }

    static public long three_powers_1(long p, long k) {
        long result = 0;
        result = Bernoulli.power_2_mod(p-2*k, p);
        result += Bernoulli.power_mod(3, p-2*k, p);
        result -= Bernoulli.power_2_mod(2*p-4*k, p);
        result -= 1;
        while (result < 0) {result += p;}
        while (result >= p) {result -= p;}
        return result;
    }

    static public long three_powers_2(long p, long k) {
        long result = 0;
        result = Bernoulli.power_2_mod(2*p-4*k, p);
        result += Bernoulli.power_mod(3, p-2*k, p);
        result -= Bernoulli.power_mod(6, p-2*k, p);
        result -= 1;
        while (result < 0) {result += p;}
        while (result >= p) {result -= p;}
        return result;
    }

    static public long three_powers_3(long p, long k) {
        long result = 0;
        result = Bernoulli.power_2_mod(2*p-4*k, p);
        result += Bernoulli.power_mod(5, p-2*k, p);
        result -= Bernoulli.power_2_mod(3*p-6*k, p);
        result -= 1;
        while (result < 0) {result += p;}
        while (result >= p) {result -= p;}
        return result;
    }

    static public long three_powers_4(long p, long k) {
        long result = 0;
        result = Bernoulli.power_2_mod(p-2*k, p*p*p);
        result *= p;
        while (result < 0) {result += p*p*p;}
        while (result >= p*p*p) {result -= p*p*p;}
        return result;
    }

    static public long sum_1(long p, long k) {
        long begin = (long) Math.ceil((double) p / 4.0);
        long end = (long) Math.ceil((double) p / 3.0);
        long j = 0, result = 0;
        for (j=begin; j<end; j++) {
            result += Bernoulli.power_mod(j, 2*k-1, p);
        }
        while (result < 0) {result += p;}
        while (result >= p) {result -= p;}
        return result;
    }

    static public long sum_2(long p, long k) {
        long begin = (long) Math.ceil((double) p / 6.0);
        long end = (long) Math.ceil((double) p / 4.0);
        long j = 0, result = 0;
        for (j=begin; j<end; j++) {
            result += Bernoulli.power_mod(j, 2*k-1, p);
        }
        while (result < 0) {result += p;}
        while (result >= p) {result -= p;}
        return result;
    }

    static public long sum_3(long p, long k) {
        long begin = (long) Math.ceil((double) p / 8.0);
        long end = (long) Math.ceil((double) p / 5.0);
        long j = 0, result = 0;
        for (j=begin; j<end; j++) {
            result += Bernoulli.power_mod(j, 2*k-1, p);
        }
        begin = (long) Math.ceil((double) 3*p / 8.0);
        end = (long) Math.ceil((double) 2*p / 5.0);
        for (j=begin; j<end; j++) {
            result += Bernoulli.power_mod(j, 2*k-1, p);
        }
        while (result < 0) {result += p;}
        while (result >= p) {result -= p;}
        return result;
    }

    static public long sum_4(long p, long k) {
        long begin = 1;
        long end = (long) ((double) p-1)/2;
        long j = 0, result = 0;
        for (j=begin; j<end; j++) {
            result += Bernoulli.power_mod(p-2*j, 2*k, p*p*p);
        }
        while (result < 0) {result += p*p*p;}
        while (result >= p*p*p) {result -= p*p*p;}
        return result;
    }

    public static void main(String[] args) {
        long [] primes = new long[num_primes];
        int i = 0, k = 0;
        long p = 0, t_1 = 0, t_2 = 0, t_3 = 0, t_4 = 0;
        long s_1 = 0, s_2 = 0, s_3 = 0, s_4 = 0;
        boolean go_t2 = false, go_t3 = false, go_t4 = false, go_t5 = false;
        long t2_reached = 0, t3_reached = 0, t4_reached = 0;
        primes = Bernoulli.calc_primes();
        for (i=0; i<num_primes; i++) {
            p = primes[i];
            if (p == 0) {break;}
            for (k=3; k<=(p-3)/2; k++) {
                t_1 = Bernoulli.three_powers_1(p, k);
                if (t_1 == 0) {
                    // test 1 is inconclusive
                    go_t2 = true;
                    t2_reached++;
                } else {
                    s_1 = sum_1(p, k);
                    if (s_1 == 0) {
                        System.out.print("t1: ");
                        System.out.print(p);
                        System.out.print(" ");
                        System.out.println(2*k);
                    }
                }
                if (go_t2) {
                    go_t2 = false;
                    t_2 = Bernoulli.three_powers_2(p, k);
                    if (t_2 == 0) {
                        // test 1 is inconclusive
                        go_t3 = true;
                        t3_reached++;
                    } else {
                        s_2 = sum_2(p, k);
                        if (s_2 == 0) {
                            System.out.print("t2: ");
                            System.out.print(p);
                            System.out.print(" ");
                            System.out.println(2*k);
                        }
                    }
                }
                if (go_t3) {
                    go_t3 = false;
                    t_3 = Bernoulli.three_powers_3(p, k);
                    if (t_3 == 0) {
                        // test 1 is inconclusive
                        go_t4 = true;
                        t4_reached++;
                    } else {
                        s_3 = sum_3(p, k);
                        if (s_3 == 0) {
                            System.out.print("t3: ");
                            System.out.print(p);
                            System.out.print(" ");
                            System.out.println(2*k);
                        }
                    }
                }
                if (go_t4) {
                    go_t4 = false;
                    if (2*k % (p-1) == 2) {
                        System.out.print("Inconclusive1: ");
                        System.out.print(p);
                        System.out.print(" ");
                        System.out.println(2*k);
                    }
                    t_4 = Bernoulli.three_powers_4(p, k);
                    if (t_4 == 0) {
                        System.out.print("Inconclusive2: ");
                        System.out.print(p);
                        System.out.print(" ");
                        System.out.println(2*k);
                    } else {
                        s_4 = sum_4(p, k);
                        if (s_4 == 0) {
                            System.out.print("t4: ");
                            System.out.print(p);
                            System.out.print(" ");
                            System.out.println(2*k);
                        }
                    }
                }
            }
        }
        System.out.print("t2: ");
        System.out.print(t2_reached);
        System.out.print(" t3: ");
        System.out.print(t3_reached);
        System.out.print(" t4: ");
        System.out.println(t4_reached);
    }

}
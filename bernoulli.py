MAX_PRIME = 1000

def calc_primes() -> list[int]:
    """Returns a list of all primes up to MAX_PRIME."""
    sieve = [0, 0] + [1] * (MAX_PRIME - 2)
    for i, n in enumerate(sieve):
        if n == 1:
            for j in range(2*i, MAX_PRIME, i):
                sieve[j] = 0
    sieve[2] = 0
    sieve[3] = 0
    sieve[5] = 0
    sieve[7] = 0
    primes = []
    for i, n in enumerate(sieve):
        if n == 1:
            primes.append(i)
    return primes

def binary_places(n: int) -> int:
    for i in range(64):
        if (n >> i) == 0:
            break
    return i

def power_mod(n: int, k: int, p: int) -> int:
    """Calculates n**k (mod p) keeping size under 8 bytes."""
    result = n
    bin_pl = binary_places(n)
    for i in range(1, k):
        if result >> (64 - bin_pl - 1) == 0:
            result *= n
        else:
            result %= p
            result *= n
    return result % p

def power_2_mod(k: int, p: int) -> int:
    """Calculats 2^k (mod p) using bit shifting, in 8 bytes."""
    result = 2
    for i in range(1, k):
        if result >> 62 == 0:
            result = result << 1
        else:
            result %= p
            result = result << 1
    return result % p

def three_powers_1(p: int, k: int) -> int:
    """Calculates the 3 powers part of Vandiver's Thm 1.
    
    Notice that this k matches 2k in Bernoulli.md"""
    result = power_2_mod(p-2*k, p)
    result += power_mod(3, p-2*k, p)
    result -= power_2_mod(2*p-4*k, p)
    result -= 1
    while (result < 0):
        result += p
    while (result >= p):
        result -= p
    return result

def three_powers_2(p: int, k: int) -> int:
    """Calculates the 3 powers part of Vandiver's Thm 2."""
    result = power_2_mod(2*p-4*k, p)
    result += power_mod(3, p-2*k, p)
    result -= power_mod(6, p-2*k, p)
    result -= 1
    while (result < 0):
        result += p
    while (result >= p):
        result -= p
    return result

def three_powers_3(p: int, k: int) -> int:
    """Calculates the 3 powers part of Vandiver's Thm 3."""
    result = power_2_mod(2*p-4*k, p)
    result += power_mod(5, p-2*k, p)
    result -= power_2_mod(3*p-6*k, p)
    result -= 1
    while (result < 0):
        result += p
    while (result >= p):
        result -= p
    return result

def three_powers_4(p: int, k: int) -> int:
    """Calculates the left side of Vandiver's Thm 4.
    
    This is clearly not a sum of three powers, but I'm 
    calling it that just for naming consistency."""
    result = power_2_mod(2*k-1, p**3)
    result *= p
    while (result < 0):
        result += p**3
    while (result >= p):
        result -= p**3
    return result

def sum_1(p: int, k: int) -> int:
    """Calculates the sum part of Vandiver's Thm 1."""
    begin = int(p/4) + 1
    end = int(p/3) + 1
    result = 0
    for j in range(begin, end):
        result += power_mod(j, 2*k-1, p)
    while (result < 0):
        result += p
    while (result >= p):
        result -= p
    return result

def sum_2(p: int, k: int) -> int:
    """Calculates the sum part of Vandiver's Thm 2."""
    begin = int(p/6) + 1
    end = int(p/4) + 1
    result = 0
    for j in range(begin, end):
        result += power_mod(j, 2*k-1, p)
    while (result < 0):
        result += p
    while (result >= p):
        result -= p
    return result

def sum_3(p: int, k: int) -> int:
    """Calculates the sum part of Vandiver's Thm 3."""
    begin = int(p/8) + 1
    end = int(p/5) + 1
    result = 0
    for j in range(begin, end):
        result += power_mod(j, 2*k-1, p)
    begin = int(3*p/8) + 1
    end = int(2*p/5) + 1
    for j in range(begin, end):
        result += power_mod(j, 2*k-1, p)
    while (result < 0):
        result += p
    while (result >= p):
        result -= p
    return result

def sum_4(p: int, k: int) -> int:
    """Calculates the sum part of Vandiver's Thm 4."""
    begin = 1
    end = (p-1)//2
    result = 0
    for j in range(begin, end):
        result += power_mod(p-2*j, 2*k, p**3)
    while (result < 0):
        result += p**3
    while (result >= p**3):
        result -= p**3
    return result

def main():
    go_t_1 = go_t_2 = go_t_3 = go_t_4 = False
    t_2_reached = t_3_reached = t_4_reached = 0
    primes = calc_primes()
    for p in primes:
        for k in range(3, (p-3)//2 + 1):
            t_1 = three_powers_1(p, k)
            if (t_1 == 0):
                # test 1 is inconclusive
                go_t_2 = True
                t_2_reached += 1
            else:
                s_1 = sum_1(p, k)
                if (s_1 == 0):
                    print(f"t1: {p} {2*k}")
            if go_t_2:
                go_t_2 = False
                t_2 = three_powers_2(p, k)
                if (t_2 == 0):
                    # test 2 is inconclusive
                    go_t_3 = True
                    t_3_reached += 1
                else:
                    s_2 = sum_2(p, k)
                    if (s_2 == 0):
                        print(f"t2: {p} {2*k}")
            if go_t_3:
                go_t_3 = False
                t_3 = three_powers_3(p, k)
                if (t_3 == 0):
                    # test 3 is inconclusive
                    go_t_4 = True
                    t_4_reached += 1
                else:
                    s_3 = sum_3(p, k)
                    if s_3 == 0:
                        print(f"t3: {p} {2*k}")
            if go_t_4:
                go_t_4 = False
                if 2*k % (p-1) == 2:
                    print(f"Inconclusive: {p} {2*k}")
                t_4 = three_powers_4(p, k)
                if (t_4 == 0):
                    print(f"Inconclusive: {p} {2*k}")
                else:
                    s_4 = sum_4(p, k)
                    if (s_4 == 0):
                        print(f"t4: {p} {2*k}")
    print(f"test2: {t_2_reached} test3: {t_3_reached} test4:{t_4_reached}")

main()
import ctypes

NUM_PRIMES = 168

def main():
    ber_lib = ctypes.CDLL("bernoulli_clib.so")

    PrimesArray = ctypes.c_int64 * NUM_PRIMES
    primes_array = PrimesArray()

    ber_lib.calc_primes.argtypes = [PrimesArray]
    ber_lib.calc_primes.restype = None
    ber_lib.test_1.argtypes = [ctypes.c_int64, ctypes.c_int64]
    ber_lib.test_1.restype = ctypes.c_int64

    ber_lib.calc_primes(primes_array)

    for p in primes_array:
        if p == 0: break
        for k in range(3, (p-3)//2 + 1):
            go_to_t2 = False
            go_to_t3 = False
            go_to_t4 = False
            t_1 = ber_lib.test_1(p, k)
            if t_1 == 1:
                print("t1:", p, 2*k)
            elif t_1 == -1:
                go_to_t2 = True
            if go_to_t2:
                t_2 = ber_lib.test_2(p, k)
                if t_2 == 1:
                    print("t2:", p, 2*k)
                elif t_2 == -1:
                    go_to_t3 = True
            if go_to_t3:
                t_3 = ber_lib.test_3(p, k)
                if t_3 == 1:
                    print("t3:", p, 2*k)
                elif t_3 == -1:
                    go_to_t4 = True
            if go_to_t4:
                t_4 = ber_lib.test_4(p, k)
                if t_4 == 1:
                    print("t4:", p, 2*k)
                elif t_4 == -1:
                    print("All 4 tests inconclusive.")





if __name__ == "__main__":
    main()
        
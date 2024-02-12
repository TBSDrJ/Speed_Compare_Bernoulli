program bernoulli_fortran
    implicit none
    integer(kind = 8), parameter :: max_prime = 1000
    integer(kind = 8), parameter :: num_primes = 170
    integer(kind = 8) :: i, j, k, p, t1, t2, t3, t4, s1, s2, s3, s4
    integer(kind = 8) :: primes(num_primes)
    logical :: go_t2, go_t3, go_t4
    integer(kind = 8) :: t2_reached, t3_reached, t4_reached
    integer(kind = 8) :: results(num_primes, 3)
    j = 1
    primes(:) = 0
    results(:,:) = 0
    go_t2 = .false.
    go_t3 = .false.
    go_t4 = .false.
    t2_reached = 0
    t3_reached = 0
    t4_reached = 0
    primes = calc_primes()
    primes_loop: do i = 1, num_primes
        p = primes(i)
        if (p == 0) then
            exit
        end if
        indices_loop: do k = 3, (p-3)/2
            t1 = three_powers_1(p, k)
            if (t1 == 0) then
                ! test1 is inconclusive
                go_t2 = .true.
                t2_reached = t2_reached + 1
            else
                s1 = sum_1(p,k)
                if (s1 == 0) then
                    ! print *, "test1", p, 2*k
                    results(j, 1) = 1
                    results(j, 2) = p
                    results(j, 3) = 2*k
                    j = j + 1
                end if
            end if
            if (go_t2) then
                go_t2 = .false.
                t2 = three_powers_2(p, k)
                if (t2 == 0) then
                    ! test2 is inconclusive
                    go_t3 = .true.
                    t3_reached = t3_reached + 1
                else
                    s2 = sum_2(p,k)
                    if (s2 == 0) then
                        ! print *, "test2", p, 2*k
                        results(j, 1) = 2
                        results(j, 2) = p
                        results(j, 3) = 2*k
                        j = j + 1
                    end if
                end if   
            end if         
            if (go_t3) then
                go_t3 = .false.
                t3 = three_powers_3(p, k)
                if (t3 == 0) then
                    ! test2 is inconclusive
                    go_t4 = .true.
                    t4_reached = t4_reached + 1
                else
                    s3 = sum_3(p,k)
                    if (s3 == 0) then
                        ! print *, "test3", p, 2*k
                        results(j, 1) = 3
                        results(j, 2) = p
                        results(j, 3) = 2*k
                        j = j + 1
                    end if
                end if
            end if
            if (go_t4) then
                go_t4 = .false.
                t4 = three_powers_4(p, k)
                if (t4 == 0) then
                    ! test2 is inconclusive
                    ! print *, "Inconclusive", p, 2*k
                    results(j, 1) = 5
                    results(j, 2) = 2
                    results(j, 3) = 2*k
                    j = j + 1
                else
                    s4 = sum_4(p,k)
                    if (s4 == 0) then
                        ! print *, "test4", p, 2*k
                        results(j, 1) = 4
                        results(j, 2) = p
                        results(j, 3) = 2*k
                        j = j + 1
                    end if
                end if
            end if
        end do indices_loop
    end do primes_loop
    do i = 1, num_primes
        if (results(i, 1) == 0) then
            exit
        end if
        print *, results(i, 1), results(i, 2), results(i, 3)
    end do
    print *, "test2:", t2_reached, "test3:", t3_reached, "test4:", t4_reached
    
contains
    ! returns a list of all primes up to max_primes
    function calc_primes() result(primes)
        integer(kind = 8) :: primes(num_primes)
        integer(kind = 8) :: i, j
        logical :: sieve(max_prime)
        j = 0
        sieve(:) = .true.
        sieve(1) = .false.
        do i = 2, 50
            if (sieve(i) .eqv. .true.) then
                do j = 2*i, max_prime, i
                    sieve(j) = .false.
                end do
            end if
        end do
        sieve(2) = .false.
        sieve(3) = .false.
        sieve(5) = .false.
        sieve(7) = .false.
        j = 0
        do i = 1, max_prime
            if (sieve(i) .eqv. .true.) then
                primes(j) = i
                j = j + 1
            end if
        end do
    end function calc_primes

    ! Returns n to the k power (mod p) even when n^k
    !   is much too large to fit in the data type.
    function power_mod(n, k, p) result(res)
        implicit none
        integer(kind = 8), intent(in) :: n, k, p
        integer(kind = 8) :: res, lz_n, i
        res = n
        lz_n = leadz(n)
        do i = 2, k
            if (leadz(res) > lz_n) then
                res = res * n
            else
                res = mod(res, p)
                res = res * n
            end if
        end do
        res = mod(res, p)
    end function power_mod

    ! Returns 2 to the k power (mod p) even when 2^k
    !   is much too large to fit in the data type.
    ! This is separate from power_mod because bitshifting
    !   is way faster.
    function power_2_mod(k, p) result(res)
        implicit none
        integer(kind = 8), intent(in) :: k, p
        integer(kind = 8) :: i, res
        res = 2
        do i = 2, k
            if (leadz(res) > 61) then
                res = shiftl(res, 1)
            else
                res = mod(res, p)
                res = shiftl(res, 1)
            end if
        end do
        res = mod(res, p)
    end function power_2_mod

    ! Computes the 3 powers part of Vandiver's Thm 1.
    function three_powers_1(p, k) result(res)
        implicit none
        integer(kind = 8), intent(in) :: k, p
        integer(kind = 8) :: res
        res = power_2_mod(p-2*k, p)
        res = res + power_mod(int(3, kind=8), p-2*k, p)
        res = res - power_2_mod(2*p-4*k, p)
        res = res - 1
        do while (res < 0)
            res = res + p
        end do
        do while (res >= p) 
            res = res - p
        end do
    end function three_powers_1

    ! Computes the 3 powers part of Vandiver's Thm 2.
    function three_powers_2(p, k) result(res)
        implicit none
        integer(kind = 8), intent(in) :: k, p
        integer(kind = 8) :: res
        res = power_2_mod(2*p-4*k, p)
        res = res + power_mod(int(3, kind=8), p-2*k, p)
        res = res - power_mod(int(6, kind=8), p-2*k, p)
        res = res - 1
        do while (res < 0)
            res = res + p
        end do
        do while (res >= p) 
            res = res - p
        end do
    end function three_powers_2

    ! Computes the 3 powers part of Vandiver's Thm 3.
    function three_powers_3(p, k) result(res)
        implicit none
        integer(kind = 8), intent(in) :: k, p
        integer(kind = 8) :: res
        res = power_2_mod(2*p-4*k, p)
        res = res + power_mod(int(5, kind=8), p-2*k, p)
        res = res - power_2_mod(3*p-6*k, p)
        res = res - 1
        do while (res < 0)
            res = res + p
        end do
        do while (res >= p) 
            res = res - p
        end do
    end function three_powers_3

    ! Computes the 3 powers part of Vandiver's Thm 4.
    function three_powers_4(p, k) result(res)
        implicit none
        integer(kind = 8), intent(in) :: k, p
        integer(kind = 8) :: res
        res = power_2_mod(2*k - 1, p**3)
        res = res * p
        do while (res < 0)
            res = res + p**3
        end do
        do while (res >= p**3) 
            res = res - p**3
        end do
    end function three_powers_4

    ! Computes the sum part of Vandiver's Thm 1.
    function sum_1(p, k) result(res)
        implicit none
        integer(kind = 8), intent(in) :: p, k
        integer(kind = 8) :: res, first, last, j
        res = 0
        first = p / 4 + 1
        last = p / 3
        do j = first, last
            res = res + power_mod(j, 2*k-1, p)
        end do
        do while (res < 0)
            res = res + p
        end do
        do while (res >= p) 
            res = res - p
        end do
    end function sum_1

    ! Computes the sum part of Vandiver's Thm 2.
    function sum_2(p, k) result(res)
        implicit none
        integer(kind = 8), intent(in) :: p, k
        integer(kind = 8) :: res, first, last, j
        res = 0
        first = p / 6 + 1
        last = p / 4
        do j = first, last
            res = res + power_mod(j, 2*k-1, p)
        end do
        do while (res < 0)
            res = res + p
        end do
        do while (res >= p) 
            res = res - p
        end do
    end function sum_2

    ! Computes the sum part of Vandiver's Thm 3.
    function sum_3(p, k) result(res)
        implicit none
        integer(kind = 8), intent(in) :: p, k
        integer(kind = 8) :: res, first, last, j
        res = 0
        first = p / 8 + 1
        last = p / 5
        do j = first, last
            res = res + power_mod(j, 2*k-1, p)
        end do
        first = 3 * p / 8 + 1
        last = 2 * p / 5
        do j = first, last
            res = res + power_mod(j, 2*k-1, p)
        end do
        do while (res < 0)
            res = res + p
        end do
        do while (res >= p) 
            res = res - p
        end do
    end function sum_3

    ! Computes the sum part of Vandiver's Thm 4.
    function sum_4(p, k) result(res)
        implicit none
        integer(kind = 8), intent(in) :: p, k
        integer(kind = 8) :: res, first, last, j
        res = 0
        first = 1
        last = (p-1) / 2
        do j = first, last
            res = res + power_mod(p-2*j, 2*k, p**3)
        end do
        do while (res < 0)
            res = res + p**3
        end do
        do while (res >= p**3) 
            res = res - p**3
        end do
    end function sum_4
end program bernoulli_fortran



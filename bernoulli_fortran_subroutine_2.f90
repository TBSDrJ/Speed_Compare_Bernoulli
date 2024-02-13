program bernoulli_fortran
    implicit none
    integer(kind = 8), parameter :: max_prime = 1000
    integer(kind = 8), parameter :: num_primes = 170
    integer(kind = 8) :: i, j, k, p, t1, t2, t3, t4, s1, s2, s3, s4
    integer(kind = 8) :: pm, p2m
    integer(kind = 8) :: primes(num_primes)
    logical :: go_t2, go_t3, go_t4
    integer(kind = 8) :: t2_reached, t3_reached, t4_reached
    primes(:) = 0
    go_t2 = .false.
    go_t3 = .false.
    go_t4 = .false.
    t2_reached = 0
    t3_reached = 0
    t4_reached = 0
    call calc_primes(primes)
    primes_loop: do i = 1, num_primes
        p = primes(i)
        if (p == 0) then
            exit
        end if
        indices_loop: do k = 3, (p-3)/2
            call power_2_mod(p-2*k, p, pm)
            t1 = pm
            call power_mod(int(3, kind=8), p-2*k, p, pm)
            t1 = t1 + pm
            call power_2_mod(2*p-4*k, p, p2m)
            t1 = t1 - p2m - 1
            do while (t1 < 0)
                t1 = t1 + p
            end do
            do while (t1 >= p) 
                t1 = t1 - p
            end do
            if (t1 == 0) then
                ! test1 is inconclusive
                go_t2 = .true.
                t2_reached = t2_reached + 1
            else
                s1 = 0
                first = p / 4 + 1
                last = p / 3
                do j = first, last
                    call power_mod(j, 2*k-1, p, pm)
                    s1 = s1 + pm
                end do
                do while (s1 < 0)
                    s1 = s1 + p
                end do
                do while (s1 >= p) 
                    s1 = s1 - p
                end do
                if (s1 == 0) then
                    print *, "test1", p, 2*k
                end if
            end if
            if (go_t2) then
                go_t2 = .false.
                call power_2_mod(2*p-4*k, p, p2m)
                t2 = p2m
                call power_mod(int(3, kind=8), p-2*k, p, pm)
                t2 = t2 + pm
                call power_mod(int(6, kind=8), p-2*k, p, pm)
                t2 = t2 - pm - 1
                do while (t2 < 0)
                    t2 = t2 + p
                end do
                do while (t2 >= p) 
                    t2 = t2 - p
                end do
                if (t2 == 0) then
                    ! test2 is inconclusive
                    go_t3 = .true.
                    t3_reached = t3_reached + 1
                else
                    s2 = 0
                    first = p / 6 + 1
                    last = p / 4
                    do j = first, last
                        call power_mod(j, 2*k-1, p, pm)
                        s2 = s2 + pm
                    end do
                    do while (s2 < 0)
                        s2 = s2 + p
                    end do
                    do while (s2 >= p) 
                        s2 = s2 - p
                    end do
                    if (s2 == 0) then
                        print *, "test2", p, 2*k
                    end if
                end if   
            end if         
            if (go_t3) then
                go_t3 = .false.
                call power_2_mod(2*p-4*k, p, p2m)
                t3 = p2m
                call power_mod(int(5, kind=8), p-2*k, p, pm)
                t3 = t3 + pm
                call power_2_mod(3*p-6*k, p, p2m)
                t3 = t3 - p2m - 1
                do while (t3 < 0)
                    t3 = t3 + p
                end do
                do while (t3 >= p) 
                    t3 = t3 - p
                end do
                if (t3 == 0) then
                    ! test2 is inconclusive
                    go_t4 = .true.
                    t4_reached = t4_reached + 1
                else
                    s3 = 0
                    first = p / 8 + 1
                    last = p / 5
                    do j = first, last
                        call power_mod(j, 2*k-1, p, pm)
                        s3 = s3 + pm
                    end do
                    first = 3 * p / 8 + 1
                    last = 2 * p / 5
                    do j = first, last
                        call power_mod(j, 2*k-1, p, pm)
                        s3 = s3 + pm
                    end do
                    do while (res < 0)
                        s3 = s3 + p
                    end do
                    do while (s3 >= p) 
                        s3 = s3 - p
                    end do
                    if (s3 == 0) then
                        print *, "test3", p, 2*k
                    end if
                end if
            end if
            if (go_t4) then
                go_t4 = .false.
                call power_2_mod(2*k - 1, p**3, p2m)
                t4 = p2m
                t4 = t4 * p
                do while (t4 < 0)
                    t4 = t4 + p**3
                end do
                do while (t4 >= p**3) 
                    t4 = t4 - p**3
                end do
                if (t4 == 0) then
                    ! test2 is inconclusive
                    print *, "Inconclusive", p, 2*k
                else
                    s4 = 0
                    first = 1
                    last = (p-1) / 2
                    do j = first, last
                        call power_mod(p-2*j, 2*k, p**3, pm)
                        s4 = s4 + pm
                    end do
                    do while (s4 < 0)
                        s4 = s4 + p**3
                    end do
                    do while (s4 >= p**3) 
                        s4 = s4 - p**3
                    end do
                    if (s4 == 0) then
                        print *, "test4", p, 2*k
                    end if
                end if
            end if
        end do indices_loop
    end do primes_loop
    print *, "test2:", t2_reached, "test3:", t3_reached, "test4:", t4_reached
contains

    ! returns a list of all primes up to max_primes
    subroutine calc_primes(primes)
        integer(kind = 8), intent(out) :: primes(num_primes)
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
    end subroutine calc_primes

    ! Returns n to the k power (mod p) even when n^k
    !   is much too large to fit in the data type.
    subroutine power_mod(n, k, p, res)
        implicit none
        integer(kind = 8), intent(in) :: n, k, p
        integer(kind = 8), intent(out) :: res
        integer(kind = 8) :: lz_n, i
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
    end subroutine power_mod

    ! Returns 2 to the k power (mod p) even when 2^k
    !   is much too large to fit in the data type.
    ! This is separate from power_mod because bitshifting
    !   is way faster.
    subroutine power_2_mod(k, p, res)
        implicit none
        integer(kind = 8), intent(in) :: k, p
        integer(kind = 8), intent(out) :: res
        integer(kind = 8) :: i
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
    end subroutine power_2_mod
end program bernoulli_fortran



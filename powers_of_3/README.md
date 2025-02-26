# Calculate Powers of 3

I decided to try seeing if it would be faster to find powers of 3 by creating ternary numbers using pairs of bits representing a 'trit.'  So, each pair of bits stores 00, 01, or 10 for the three ternary digits.  Then, multiplying/dividing by 3 is just a bit shift of 2 bits.

In my case, I need large powers of $3 \pmod{p}$, so I really only need the modulus operator as far as arithmetic other than multiplication by 3.  I decided as a first pass to just convert back to base 10, take modulus there, and then convert back to trits.  This ended up being pretty slow, about 3x the time compared to a simple power_mod function.

|C trit shift|C power_mod |
|:--:|:--:|
|time, RAM   |time, RAM   |
|3.17s, 983k  |0.937s, 973k  |

So, if the trit_shift is going to work, I'll have to work out a much faster way to calculate the $\pmod{p}$ part.  It makes sense to me that converting back and forth is slow -- converting into decimal requires 32 `int_64` multiplications, which is making up for any gains.  The conversion from decimal to trits is all subtractions and bit shift, so that's probably faster.

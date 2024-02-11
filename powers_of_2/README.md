# Calculate Powers of 2:

It is possible to calculate $2^k$ either by using a built-in exponentiation function, or by bit-shifting a 1 over $k$ times.  In these, I calculated $2^0$, through $2^30$, assigning each to an `unsigned int` variable, 10 million times.

|C, bit shift|C, pow(2,k) |
|:----------:|:----------:|
|time  |RAM  |time  |RAM  |
|:----:|:---:|:----:|:---:|
|0.33s |929k |1.263s|940k |

So, if you were curious: Yes, Virginia, there is a Santa Claus: bitshifting gives you back time and memory for free.
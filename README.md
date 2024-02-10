# Bernoulli Number computations

The goal of this repo is primarily to compare efficiency of different languages in carrying out numerical calculation.  The vehicle I will use for this is testing to go through the Bernoulli Numbers and calculate whether or not they are _irregular_ (see below for details), and, if they are, determine their _index of irregularity_.

I wrote a brief survey of where Bernoulli numbers come from and why and how we might calculate all this stuff [here](Bernoulli.md).

# Tests:

In all of the tests, I am calculating time/memory using a Macbook Pro with an M1 Max processor running the following at command-line:

```/usr/bin/time -l program```

Each is run 3 times, I take the average of the three.  The time value reported here is only the 'user' value, excluding the 'system' time.  The 'RAM' value reported is the 'peak memory footprint.'

## Calculate Powers of 2:

See folder 'powers_of_2' for code.

It is possible to calculate $2^k$ either by using a built-in exponentiation function, or by bit-shifting a 1 over $k$ times.  In these, I calculated $2^0$, through $2^30$, assigning each to an `unsigned int` variable, 10 million times.

|C, bit shift|C, pow(2,k) |
|:----------:|:----------:|
|time  |RAM  |time  |RAM  |
|:----:|:---:|:----:|:---:|
|0.33s |929k |1.263s|940k |

So, if you were curious: Yes, Virginia, there is a Santa Claus: bitshifting gives you back time and memory for free.

## 
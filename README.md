# Bernoulli Number computations

The goal of this repo is primarily to compare efficiency of different languages in carrying out numerical calculation.  The vehicle I will use for this is testing to go through the Bernoulli Numbers and calculate whether or not they are _irregular_ (see below for details), and, if they are, determine their _index of irregularity_.

I wrote a brief survey of where Bernoulli numbers come from and why and how we might calculate all this stuff [here](Bernoulli.md).

# Test Assumptions

In all of the tests, I am calculating time/memory using a Macbook Pro with an M1 Max processor running the following at command-line:

```/usr/bin/time -l program```

Each is run 3 times, I take the average of the three.  The time value reported here is only the 'user' value, excluding the 'system' time.  The 'RAM' value reported is the 'peak memory footprint.'  I'm using kB = 1000 bytes and mB = 1000000 bytes.

I'm checking all of the integers less than 1000 for these tests.

I'm compiling C and C++ code using the 2011 standard (`--std=c11` `--std=c++11`).  I am running with multiple optimization flags on compile, see the table for details.

## Results

When the table says, e.g. 'v1' that's my version number.

|Setup                 |Time     |RAM    |
|:--------------------:|:-------:|:-----:|
|C, no flags           |1.637 sec|940kB  |
|C, -O1 flag           |1.223 sec|940kB  |
|C, -O2 flag           |1.223 sec|940kB  |
|C, -Ofast flag        |1.227 sec|940kB  |
|C++ v1, no flags      |1.630 sec|951kB  |
|C++ v1, -O1 flag      |1.230 sec|962kB  |
|C++ v1, -O2 flag      |1.227 sec|956kB  |
|C++ v1, -Ofast flag   |1.220 sec|951kB  |
|Python v1, with 3.10  |63.46 sec|5.763mB|
|Python v1, with 3.11  |47.36 sec|6.849mB|

An obvious conclusion from this is: "Python sux."  That is **so** not where I am going with this -- notice that the top language supported by Torch and Tensorflow is Python, and for good reasons.  The correct conclusion is: If you're doing serious number-crunching, don't do it in pure simple Python.  Pure Python is great for lots of stuff, I teach multiple years of it, I'm a huge supporter of Python and these results are not changing that at all.  It's not the right tool for every job.  Nor is C or Fortran the right tool for every job, even if they are much faster at number-crunching.

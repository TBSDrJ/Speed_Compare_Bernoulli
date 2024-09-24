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

In order by speed:

|Setup                 |Time     |RAM     |
|:--------------------:|:-------:|:------:|
|C++, -Ofast flag      |1.220 sec|951 kB  |
|C, -O2 flag           |1.223 sec|940 kB  |
|C, -O1 flag           |1.223 sec|940 kB  |
|C, -Ofast flag        |1.227 sec|940 kB  |
|C++, -O2 flag         |1.227 sec|956 kB  |
|C++, -O1 flag         |1.230 sec|962 kB  |
|C++, no flags         |1.630 sec|951 kB  |
|C, no flags           |1.637 sec|940 kB  |
|Pypy 3.10             |1.763 sec|26.81 mB|
|Java                  |1.920 sec|7.916 mB|
|C++, int, -O2 flag    |2.070 sec|962 kB  |
|C++, int, -Ofast flag |2.073 sec|956 kB  |
|C++, int, -O1 flag    |2.077 sec|956 kB  |
|C, int, -Ofast flag   |2.117 sec|935 kB  |
|C, int, -O1 flag      |2.120 sec|935 kB  |
|C, int, -O2 flag      |2.120 sec|946 kB  |
|C, int, no flags      |2.977 sec|940 kB  |
|C++, int, no flags    |3.033 sec|951 kB  |
|Fortran 90,-Ofast flag|3.287 sec|1.033 mB|
|F90, subr, -Ofast flag|3.287 sec|1.033 mB|
|Fortran 90, -O2 flag  |3.293 sec|1.033 mB|
|Fortran 90, -O1 flag  |3.300 sec|1.038 mB|
|Fortran 90, no flags  |5.987 sec|1.038 mB|
|F90, int, no flags    |5.987 sec|1.038 mB|
|F90, subr, no flags   |6.397 sec|1.033 mB|
|JS in Chrome          |12.70 sec|?       |
|JS in Firefox         |15.48 sec|?       |
|JS in Safari          |16.61 sec|?       |
|Python, with 3.11     |47.36 sec|6.849 mB|
|Python, with 3.10     |63.46 sec|5.763 mB|
|Python, with 3.9      |65.33 sec|4.894 mB|

A series of mostly unrelated thoughts:
+ The C/C++/F90 unmarked versions use data type long for all integers, the ones marked 'int' substitute 'int' for 'long' (or kind=4 for kind=8 in F90).  Interestingly, this seems to save essentially no memory (e.g. in the C runs, some runs are using ~935kB and some ~951kB, the differences in usage are just in how many times it gets 935 vs 951.)  Interestingly, in Fortran, this didn't change a thing, where in C and C++, it slowed things down substantially.

+ I tried, in C, C++ and Fortran, to store the data and print the results at the end instead of printing as results came up, and this made essentially no difference in time.

+ I am quite surprised that Fortran was substantially slower than C, this has not been my experience with numerical computations.  I'm not sure what made this problem different.  I tried converting all the functions to subroutines to see if that would help, and it was slightly slower with no flags, and identical speed with flags.  I also tried moving all the functionality that isn't used more than once into the main function, and that also made precisely zero difference in run time (in `..._subroutine_2.f90`).

+ I am even more surprised that Java was faster than Fortran. This problem ran way faster in Java than I expected, quite different from my earlier experiences with Java.

+ An obvious conclusion from this is: "Python sux."  That is **so** not where I am going with this -- notice that the top language supported by Torch and Tensorflow is Python, and for good reasons.  The correct conclusion is: If you're doing serious number-crunching, don't do it in pure Python.  Pure Python is great for lots of stuff, I teach multiple years of it, I'm a huge supporter of Python and these results are not changing that at all.  It's not the right tool for every job.  Python is fantastic at allowing a programmer to develop much more complex code much more easily.  Nor is C or Fortran the right tool for every job, even if they are much faster at number-crunching.

+ I was going to try a couple of other versions in some languages but there is so little reliance on lists/arrays that it wasn't really worth it, the speed difference didn't show up, so I'm not going to work on that here.

+ It's pretty clear that Python is increasing memory usage as it updates versions in exchange for gaining speed.  That's probably the choice I'd make at this point too.  Personally, I wish you could use command-line options to adjust this balance as is possible with C/C++/Fortran.  I tried the -O and -OO command-line flags in both 3.10 and 3.11 and it didn't make any noticeable difference in either time or RAM for this use case.  The optimization seems mostly dedicated to reducing introspection overhead, which I'm essentially not using.

+ This is my first experience with Pypy, and ... wow!  Reading the beginning of the docs, it looks like this problem was pretty much made to make Pypy look good, but it looks _really_ good.  The idea of being able to write code in Python and get ~95% of the performance of bare C is spectacular.

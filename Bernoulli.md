# Bernoulli Numbers

## Why is this problem interesting? 

It's a little complicated, but I spent entire years of my life thinking about this kind of stuff, so I'm going to write a brief tour because I can't help myself:

## Historical starting point: Jakob Bernoulli

The first place that the Bernoulli Numbers arose was in the context of summation formulas.  Consider the following sequence of formulas (hopefully you have seen at least the first two or three before):

$$\sum_{i=1}^{k-1} i^0 = 1 + 1 + 1 + ... + 1 \text{(k times)} = k$$
$$\sum_{i=1}^{k-1} i^1 = 1 + 2 + 3 + ... + k = \frac{(k+1)(k)}{2} = \frac{1}{2}k^2 + \frac{1}{2}k$$
$$\sum_{i=1}^{k-1} i^2 = 1 + 4 + 9 + ... + (k-1)^2 = \frac{k(k+1)(2k+1)}{6} = \frac{1}{3}k^3 - \frac{1}{2}k^2 + \frac{1}{6}k$$
$$\sum_{i=1}^{k-1} i^3 = 1 + 8 + 27 + ... + (k-1)^3 = \frac{k^2(k-1)^2}{4} = \frac{1}{4}k^4 - \frac{1}{2}k^3 + \frac{1}{4}k^2$$
$$\sum_{i=1}^{k-1} i^4 = 1 + 16 + 81 + ... + (k-1)^4 = \frac{k(k-1)(2k-1)(3k^2-3k-1)}{30} = \frac{1}{5}k^5 - \frac{1}{2}k^4 + \frac{1}{3}k^3 - \frac{1}{30}k$$

(The last one I didn't know off the top of my head, I'm following [this source](https://maa.org/press/periodicals/convergence/sums-of-powers-of-positive-integers-pierre-de-fermat-1601-1665-france) for that, but shifted, substituting my $k-1$ for her $n$.)

Then, the $n^{\text{th}}$ Bernoulli Number is the coefficient of $k$ in the formula for $\sum_{i=1}^{k-1} i^n$.  So, by this definition, the first  Bernoulli Numbers are:

$$B_0 = 1$$
$$B_1 = -\frac{1}{2}$$
$$B_2 = \frac{1}{6}$$
$$B_3 = 0$$
$$B_4 = -\frac{1}{30}$$
$$\ldots$$

## Warning about notation

_Note:_ We choose to end with $k-1$ instead of $k$ in order to maintain consistency with some more modern developments in the usage and theory of Bernoulli numbers -- Jakob Bernoulli would have used $k$ and ended up with $B_1 = +\frac{1}{2}$ instead; the others remain the same.  Also note that it is common to ignore the odd-indexed Bernoulli numbers because all of them after $B_1$ are zero.  So, in many modern sources, you will see $B_1 = \frac{1}{6}$, $B_2 = -\frac{1}{30}$ and so on.

## Later steps in the development of Bernoulli numbers

If you want to read more about the emergence of the role of the Bernoulli Numbers in classical number theory and algebra, I found Paulo Ribenboim's _13 Lectures on Fermat's Last Theorem_ to be very helpful (though I was a couple of years into graduate study in mathematics before I read it, so YMMV).

We know better ways to compute them now, and we certainly know a lot more about them than Jakob Bernoulli ever did.  There are a couple of important properties to know:

+ The Bernoulli numbers are all rational numbers, so they are fractions with an integer numerator and integer denominator.
+ They alternate between positive and negative.
+ The numerators grow at $O(n^n)$ -- "wicked fast" as we'd say in New England.  That's way faster than exponential, even faster than factorial.  
+ The numerators grow much more slowly, and we have much more information about what is in them.
+ From the Online Encyclopedia of Integer Sequences: [Numerators](http://oeis.org/A000367) and [Denominators](http://oeis.org/A002445).  (I was looking for a minute: "Why don't they have a sequence of the fractions?" "Oh, right, it's the Online Encyclopedia of _Integer_ Sequences.")
+ [From Wolfram Mathworld](https://mathworld.wolfram.com/BernoulliNumber.html)

The important conclusion for us is that it is quite difficult to calculate the numerators of larger-index Bernoulli numbers, even with vast amounts of computing power. 

## Kummer and Vandiver

Following the work of EE Kummer (EE = Ernst Eduard, mid-1800s, Germany) and HS Vandiver (HS = Harry Schultz, early 1900s, Texas), it turns out to be important to understand whether a prime number divides the numerator of certain Bernoulli numbers, and, if so, how many times.  In particular, we have the following definition (in all that follows, we're going to ignore the case where $p=2$ because it is not useful and it is annoying to say "an odd prime" every time instead "a prime"):

_Definition (Kummer):_ A prime number $p$ is _regular_ if and only if $p$ does not divide the numerator of any of the Bernoulli numbers $B_2$, $B_4$, $\ldots$, $B_{p-3}$.  (c.f. [OEIS List of regular primes](https://oeis.org/A007703))

_Definitions (Kummer)_ A prime number $p$ is _irregular_ if and only if $p$ divides the numerator of one or more of the Bernoulli Numbers $B_2$, $B_4$, $\ldots$, $B_{p-3}$, and we say that the _index of irregularity_ of an irregular prime $p$ is equal to the number of different Bernoulli numbers in that sequence that $p$ divides. (c.f. [OEIS List of irregular primes](https://oeis.org/A000928), and [OEIS List of indices of irregularity](https://oeis.org/A091887))

(Note for my CS students: Make sure you think about regular vs irregular in terms of DeMorgan's Law.)

Notice that, in the first few Bernoulli numbers we calculated, all of the numerators are 1, so we haven't found any irregular primes yet. &#9785;

In computational tests like the one we are going to run in this repo, about 40% of primes turn out to be irregular.  There is a proof that there are infinitely many primes are irregular, but it is still an open problem to prove that there are infinitely many regular primes.

In order to see if a prime $p$ divides the numerator of a Bernoulli number, we will use the following tools from HS Vandiver:

For the CS students in the audience, $a \equiv b \pmod{p}$ means the same as `a % p == b % p`.

_Theorem 1 (Vandiver)_ If $p$ is prime, $p \geq 5$, $k \geq 1$, and $p-1$ does not divide $2k$, then:

$$\frac{2^{p-2k} + 3^{p-2k} - 4^{p-2k} - 1}{4k} \cdot B_{2k} \equiv \sum_{\frac{p}{4} < j < \frac{p}{3}} j^{2k-1} \pmod{p}$$

To take this apart a little, we have three quantities, going left to right:

$$\text{(Fraction)} \cdot \text{(Bernoulli number)} \equiv \text{Sum}$$

We want to know if the Bernoulli number is divisible by $p$, i.e. if the Bernoulli number $\equiv 0 \pmod{p}$.  So we have the following table of possibilities:

|Fraction|Sum     |Bernoulli number|
|:------:|:------:|:--------------:|
|nonzero |zero    |gotta be zero   |
|nonzero |nonzero |gotta be nonzero|
|zero    |anything|can't tell      |

The bottom one is kind of unfortunate, and it does come up.  So we have similar theorems we can use that have the same kind of table of possibilities also:

_Theorem 2 (Vandiver)_ If $p$ is prime, $p \geq 7$, $k \geq 1$, and $p-1$ does not divide $2k$, then:

$$\frac{4^{p-2k} + 3^{p-2k} - 6^{p-2k} - 1}{4k} \cdot B_{2k} \equiv \sum_{\frac{p}{6} < j < \frac{p}{4}} j^{2k-1} \pmod{p}$$

_Theorem 3 (Vandiver)_ If $p$ is prime, $p \geq 11$, $k \geq 1$, and $p-1$ does not divide $2k$, then:

$$\frac{4^{p-2k} + 5^{p-2k} - 8^{p-2k} - 1}{4k} \cdot B_{2k} \equiv \sum_{\frac{p}{8} < j < \frac{p}{5}} j^{2k-1} + \sum_{\frac{3p}{8} < j < \frac{2p}{5}} j^{2k-1} \pmod{p}$$

_Theorem 4 (Vandiver)_ If $p$ is prime and $2k \not \equiv 2 \pmod{p-1}, then:

$$2^{2k-1}pB_{2k} \equiv \sum_{j=1}^{(p-1)/2} (p-2j)^{2k} \pmod{p^3}$$

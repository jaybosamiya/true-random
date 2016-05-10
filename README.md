True Random
===========

> Use coin flipping to make an arguably true random number generator

Most random number generation libraries are actually PRNGs (Pseudo Random Number Generators), since computers are basically deterministic.
The library presented in this repository, however, uses the age-old concept of coin flipping along with naturally occuring delays, that occur on a multi-process system, to generate "truly" random numbers.

NOTE(!)
-------

I have learnt (through multiple helpful comments on [Reddit](https://www.reddit.com/r/programming/comments/4ipsg8/generate_truly_random_numbers/) and [HN](https://news.ycombinator.com/item?id=11667934)) that the method proposed in this is not really random (in the sense of the word: if everything else is same, then will the value be same). Hence, I would like to suggest this technique as only a way to generate some amount of entropy, and to combine it with other sources, and not use this for anything other than recreational purposes. In other words, this is a "clever trick" but is unusable for any kind of serious work.

Method
------

### `get_bit()`

A tight loop which constantly flips a single bit (serving as a coin) is run for a millisecond.
Since the number of times it would be able to flip the bit changes due to random fluctuations in time due to context switching of processes, this generates an arguably truly random bit (I would love to see a PoC that shows otherwise, however).

While it can be agreed that context switching is a deterministic process, we know that practically, the different clocks that exist due to the numerous hardware devices attached to a system, each run at a separate speed. This leads to differing boot times each time, even if hardware remains unchanged. Due to similar reasons, what would be deterministic (the context switching), now has an extra spanner thrown in its works: the clock skew. This means it would basically be impossible (again, I'd love for someone to prove me wrong) to recreate the exact conditions that led to the production of the said bit. This means that the bit is no longer deterministic. Hence, the bit is "truly" random.

### `get_fair_bit()`

Since the above generated bit might not actually have 50-50 probability of 0 and 1, we use the following table to normalize the probabilities. We repeatedly sample `get_bit()` twice, and decide based upon the results.

| First Bit | Second Bit | Result       |
|-----------|------------|--------------|
|         0 |          0 | Sample again |
|         0 |          1 | Return 0     |
|         1 |          0 | Return 1     |
|         1 |          1 | Sample again |

Assuming that each bit from `get_bit()` is independent of the previous bit, `get_fair_bit()` will return a bit with 50-50 probability of 0 or 1

### `true_random()`

By concatenating 31 values from `get_fair_bit()`, we get the binary representation of a number betweeen 0 and `TRUE_RAND_MAX` (2147483647 = 2^32 - 1). This value is returned as a `long int`, to get a signature similar to `random()` from `stdlib.h`.

Usage
-----

Compile the code by running `make`. This ends up creating a bunch of files:

+ true_random.o
+ tester
+ generate_constant_stream

Test the random number generator using `./tester`. Generate an unending stream of data using `./generate_constant_stream`.

If you wish to use the generator in your own program, simply copy `true_random.o` and `true_random.h` into your project, and use the `true_random()` function after a `#include "true_random.h"`.

License
-------

This software is licensed under the [MIT License](http://jay.mit-license.org/2016)

TODO
----

Run through standard RNG tests.
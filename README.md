True Random
===========

> Use coin flipping to make an arguably true random number generator

Most random number generation libraries are actually PRNGs (Pseudo Random Number Generators), since computers are basically deterministic.
The library presented in this repository, however, uses the age-old concept of coin flipping along with naturally occuring delays, that occur on a multi-process system, to generate truly random numbers.

Method
------

### `get_bit()`

A tight loop which constantly flips a single bit (serving as a coin) is run for a millisecond.
Since the number of times it would be able to flip the bit changes due to random fluctuations in time due to context switching of processes, this generates an arguably truly random bit (I would love to see a PoC that shows otherwise, however).

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

Test the random number generator using `./tester`.

If you wish to use the generator in your own program, simply copy `true_random.o` and `true_random.h` into your project, and use the `true_random()` function after a `#include "true_random.h"`.

License
-------

This software is licensed under the [MIT License](http://jay.mit-license.org/2016)

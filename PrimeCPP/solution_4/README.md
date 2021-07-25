# C++ solution by pro7onmatrix

![Algorithm](https://img.shields.io/badge/Algorithm-base-green)
![Faithfulness](https://img.shields.io/badge/Faithful-yes-green)
![Parallelism](https://img.shields.io/badge/Parallel-no-green)
![Bit count](https://img.shields.io/badge/Bits-1-green)

This solution implements the base algorithm using a `std::vector<bool>`
to hold the prime flags. Most functions such as determining the next
factor, counting the number of primes, and validating the results,
use C++ STL functions from the [algorithm](https://en.cppreference.com/w/cpp/algorithm)
and [numeric](https://en.cppreference.com/w/cpp/numeric) libraries.

The checking of even indices is done using
[assert](https://en.cppreference.com/w/cpp/error/assert)s and can
be disabled by providing `-DNDEBUG` to the compiler (since if the algorithm is
implemented properly, even indices should never be accessed anyways).

## Run instructions

(Linux): g++ -Ofast -std=c++17 -DNDEBUG -o PrimesCPP PrimesCPP.cpp && ./PrimesCPP

## Output
Passes: 7818, Time: 5.000359, Avg: 0.000639596, Limit: 1000000, Count: 78498, Valid: true

pro7onmatrix;7818;5.000359;1;algorithm=base,faithful=yes,bits=1

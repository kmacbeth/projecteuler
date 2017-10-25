#include "Problem0010.h"
#include "Libs/EratosthenesSieve.h"

namespace Euler {

    /**
     * Problem: Summation of primes
     *
     * The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
     *
     * Find the sum of all the primes below two million.
     */
    void Problem10::Solve()
    {
        const uint32_t kNumLimit = 2000000;

        EulerLib::EratosthenesSieve  sieve;
        EulerLib::PrimeSieve::Primes vPrimes;

        uint64_t result = 0;

        // Generate primes < 2000000
        sieve(vPrimes, kNumLimit);

        // Sum all numbers
        size_t vPrimeSize = vPrimes.size();

        for (uint32_t i = 0; i < vPrimeSize; ++i)
        {
            result += vPrimes[i];
        }

        SetAnswer(result);
    }

}
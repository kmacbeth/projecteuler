#include "Problem0005.h"

namespace Euler {

    /**
     * Problem: Smallest multiple
     *
     * 2520 is the smallest number that can be divided by each of the numbers
     * from 1 to 10 without any remainder.
     *
     * What is the smallest positive number that is evenly divisible by all of the
     * numbers from 1 to 20?
     */
    void Problem5::Solve()
    {
        // Prime numbers below 20, fast than sieving for first few primes...
        const uint64_t kPrimeList[] = {2, 3, 5, 7, 11, 13, 17, 19};
        const uint32_t kPrimeListSize = sizeof(kPrimeList) / sizeof(kPrimeList[0]);
        const uint64_t kUpperBound = 20;
        uint64_t result = 1;

        // We will find the prime factors os the smallest positive number
        // first, and we will multiply them together to find the number value.
        for (uint32_t i = 0; i < kPrimeListSize; ++i)
        {
            uint64_t factor = kPrimeList[i];

            // Find largest factor prime**n less than or equal to 20
            while ((factor * kPrimeList[i]) <= kUpperBound)
            {
                factor *= kPrimeList[i];
            }

            result *= factor;
        }

        SetAnswer(result);
    }

}
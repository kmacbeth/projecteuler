#include "Problem0047.h"
#include "Libs\EulerMath.h"
#include "Libs\PrimeFactorizer.h"

namespace Euler {

    /**
     * Problem: Distinct primes factors
     *
     * The first two consecutive numbers to have two distinct prime factors
     * are:
     *
     *      14 = 2 × 7
     *      15 = 3 × 5
     *
     * The first three consecutive numbers to have three distinct prime
     * factors are:
     *
     *  644 = 2² × 7 × 23
     *  645 = 3 × 5 × 43
     *  646 = 2 × 17 × 19.
     *
     * Find the first four consecutive integers to have four distinct prime
     * factors each. What is the first of these numbers?
     */
    void Problem47::Solve()
    {
        const uint32_t kNumDistinctPrimes = 4;
        const uint32_t kNumConsecutiveInteger = 4;
        const uint32_t kLowerBound = 2 * 3 * 5 * 7; // Lowest number satisfying 4 distinct primes
        uint32_t result = 0;

        EulerLib::PrimeFactorizer::FactorList factors;
        EulerLib::PrimeFactorizer factorize;
        bool bFound = false;
        uint32_t n = kLowerBound;

        while (!bFound)
        {
            uint32_t i = 0;

            while (i < kNumConsecutiveInteger)
            {
                factorize(n + i, factors);

                if (factors.size() != kNumDistinctPrimes)
                {
                    break;
                }
                ++i;
            }

            if (i == kNumConsecutiveInteger)
            {
                result = n;
                bFound = true;
            }

            ++n;
        }

        SetAnswer(result);
    }
}
#include "Problem0037.h"
#include "Libs/EulerMath.h"
#include "Libs/EratosthenesSieve.h"

namespace Euler {

    /**
     * Problem: Truncatable primes
     *
     * The number 3797 has an interesting property. Being prime itself, it is
     * possible to continuously remove digits from left to right, and remain
     * prime at each stage: 3797, 797, 97, and 7. Similarly we can work from
     * right to left: 3797, 379, 37, and 3.
     *
     * Find the sum of the only eleven primes that are both truncatable from
     * left to right and right to left.
     *
     * NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
     */
    void Problem37::Solve()
    {
        // Compute a sieve of primes to test.
        const uint32_t kNumPrimes = 1000000;
        EulerLib::EratosthenesSieve sieve;
        EulerLib::PrimeSieve::Primes vPrimes;

        sieve(vPrimes, kNumPrimes);

        std::set<uint32_t> sPrimes(vPrimes.begin(), vPrimes.end());
        size_t primesSize = vPrimes.size();

        // Test each primes until eleven are found out
        const uint32_t kMaxCount = 11;
        const uint32_t kBase = 10;
        const uint32_t kDividers[] = {1, 10, 100, 1000, 10000, 100000, 1000000};
        const uint32_t kMaxSingleDigit = 9;

        uint32_t count = 0;
        uint32_t result = 0;

        for (size_t i = 0; i < primesSize && count < kMaxCount; ++i)
        {
            // Do not consider such primes as truncatable
            if (vPrimes[i] < 10)
            {
                continue;
            }

            uint32_t divider = kDividers[EulerLib::CountDigits(vPrimes[i]) - 1];
            uint32_t numberRight = vPrimes[i];
            uint32_t numberLeft = vPrimes[i];
            bool bAreAllPrimes = true;

            while (numberRight > kMaxSingleDigit)
            {
                // Roll right
                numberRight = EulerLib::RightShift(numberRight, 1);
                // Roll left
                numberLeft %= divider;
                divider /= kBase;

                // Check for at least one composite number
                if (sPrimes.find(numberRight) == sPrimes.end() ||
                    sPrimes.find(numberLeft)  == sPrimes.end())
                {
                    bAreAllPrimes = false;
                    break;
                }

            }

            // Add prime to result when all truncatable primes.
            if (bAreAllPrimes)
            {
                count++;
                result += vPrimes[i];
            }
        }

        SetAnswer(result);
    }
}
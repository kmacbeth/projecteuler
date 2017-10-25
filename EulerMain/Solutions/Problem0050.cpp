#include "Problem0050.h"
#include "Libs\EulerMath.h"
#include "Libs\EratosthenesSieve.h"

namespace Euler {

    /**
     * Problem: Consecutive prime sum
     *
     * The prime 41, can be written as the sum of six consecutive primes:
     *
     *      41 = 2 + 3 + 5 + 7 + 11 + 13
     *
     * This is the longest sum of consecutive primes that adds to a prime
     * below one-hundred.
     *
     * The longest sum of consecutive primes below one-thousand that adds to a
     * prime, contains 21 terms, and is equal to 953.
     *
     * Which prime, below one-million, can be written as the sum of the most
     * consecutive primes?
     */
    void Problem50::Solve()
    {
        const uint32_t kLimit = 1000000;
        uint32_t result = 0;

        // Generate a sieve of primes
        EulerLib::EratosthenesSieve  sieve;
        EulerLib::PrimeSieve::Primes vPrimes;

        sieve(vPrimes, kLimit);

        // Generate a set for fast lookup.
        std::set<uint32_t> sPrimes(vPrimes.begin(), vPrimes.end());

        // Generate a cumulative sum of primes (cache)
        std::vector<uint32_t> vPrimeCumulativeSum;
        uint32_t currentSum = 2; // First prime

        for (uint32_t i = 1; i < vPrimes.size() && currentSum <= kLimit; ++i)
        {
            vPrimeCumulativeSum.push_back(currentSum);
            currentSum = vPrimes[i] + vPrimeCumulativeSum[i - 1];
        }

        // Using the cumulative sum, we can test longest sum first at a given
        // starting prime and last sum. If it's prime, we have the longest sum
        // For the current starting prime. Otherwise we decrement until a prime
        // is found. When a prime is found or all cumulative sum were tested,
        // we restart with a new starting prime greater than the previous one.
        // When the length is maximized, we stop because at each step we reduced
        // the maximum sum.
        uint32_t length = 1;
        uint32_t primeCumulativeSumSize = vPrimeCumulativeSum.size();

        for (uint32_t i = 0; i < primeCumulativeSumSize; ++i)
        {
            uint32_t lowestSum = (i > 0 ? vPrimeCumulativeSum[i - 1] : 0);

            for (uint32_t j = primeCumulativeSumSize - 1; j > (i + length); --j)
            {
                uint32_t longestSum = vPrimeCumulativeSum[j] - lowestSum;

                if ((j - i) > length && sPrimes.find(longestSum) != sPrimes.end())
                {
                    length = j - i;
                    result = longestSum;
                    break;
                }
            }
        }

        SetAnswer(result);
    }
}

#include "Problem0035.h"
#include "Libs/EulerMath.h"
#include "Libs/EratosthenesSieve.h"

namespace Euler {

    /**
     * Problem: Circular primes
     *
     * The number, 197, is called a circular prime because all rotations of 
     * the digits: 197, 971, and 719, are themselves prime.
     *
     * There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31,
     * 37, 71, 73, 79, and 97.
     *
     * How many circular primes are there below one million?
     */
    void Problem35::Solve()
    {
        // Circular primes below one million
        const size_t kNumPrimes = 1000000; 
        uint32_t result = 0;

        // Generate all primes below 1 millions using a sieve
        EulerLib::EratosthenesSieve sieve;
        EulerLib::PrimeSieve::Primes vPrimes;

        sieve(vPrimes, kNumPrimes);

        // Move into a set for fast lookup
        std::set<uint32_t> sPrimes(vPrimes.begin(), vPrimes.end());

        size_t primesSize = vPrimes.size();

        for (size_t i = 0; i < primesSize; ++i)
        {
            uint32_t digitCount = EulerLib::CountDigits(vPrimes[i]);
            uint32_t number = vPrimes[i];
            bool bIsCircularPrime = true;

            // Rotate the prime and check resulting number primality
            do
            {
                number = EulerLib::Rotate(number, 1, digitCount);

				if (sPrimes.find(number) == sPrimes.end())
                {
                    bIsCircularPrime = false;
                }
            }
            while (number != vPrimes[i] && bIsCircularPrime);

            if (bIsCircularPrime)
            {
                ++result;
            }
        }

        SetAnswer(result);
    }
}
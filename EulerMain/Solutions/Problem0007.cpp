#include "Problem0007.h"
#include "Libs/PrimeCounter.h"
#include "Libs/EratosthenesSieve.h"

namespace Euler {

    /**
     * Problem: 10001st prime
     *
     * By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can
     * see that the 6th prime is 13.
     *
     * What is the 10 001st prime number?
     */
    void Problem7::Solve()
    {
        EulerLib::EratosthenesSieve  sieve;
        EulerLib::PrimeSieve::Primes vPrimes;
        EulerLib::PrimeCounter       countPrime;

        uint32_t kLimit = 10001;
        uint64_t result = 0;

        // Count the number of primes below a number. When the count is above
        // 10001, try generating a prime sieve
        for(uint32_t i = 100000; i < 1000000000; i += 10000)
        {
            uint64_t count = countPrime(i);

            if(count > kLimit)
            {
                sieve(vPrimes, i);

                if(vPrimes.size() >= kLimit)
                {
                    result = vPrimes[kLimit - 1];
                    break;
                }
            }
        }

        SetAnswer(result);
    }

}
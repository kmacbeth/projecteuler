#include "Problem0027.h"
#include "Libs/EratosthenesSieve.h"

namespace Euler {

    /**
     * Problem: Quadratic primes
     *
     * Euler discovered the remarkable quadratic formula:
     *
     *        n**2 + n + 41
     *
     * It turns out that the formula will produce 40 primes for the consecutive
     * integer values 0 ≤ n ≤ 39. However, when 
     *
     *                   n = 40, 40**2 + 40 + 41 
     *
     * is divisible by 41, and certainly when n = 41, 41**2 + 41 + 41 is clearly
     * divisible by 41.
     *
     * The incredible formula n**2 − 79n + 1601 was discovered, which produces
     * 80 primes for the consecutive values 0 ≤ n ≤ 79. The product of the 
     * coefficients, −79 and 1601, is −126479.
     *
     * Considering quadratics of the form:
     *
     * n**2 + an + b, where |a| < 1000 and |b| ≤ 1000
     *
     * where |n| is the modulus/absolute value of n e.g. |11| = 11 and |−4| = 4
     *
     * Find the product of the coefficients, a and b, for the quadratic expression
     * that produces the maximum number of primes for consecutive values of n, 
     * starting with n = 0.
     */
    void Problem27::Solve()
    {
        const uint32_t kLimit = 25000;
        EulerLib::EratosthenesSieve sieve;
        EulerLib::PrimeSieve::Primes vPrimes;
        
        sieve(vPrimes, kLimit);

        // Create a boolean sieve from the primes
        std::vector<uint8_t> bvSieve(kLimit, 0);
        size_t primesSize = vPrimes.size();

        for (size_t i = 0; i < primesSize; ++i)
        {
            bvSieve[vPrimes[i]] = 1;
        }

        // Test all possibilities
        uint32_t maxNumPrime = 0;
        int32_t  result = 0;

        for (int32_t a = -999; a < 1000; ++a)
        {
            for (int32_t b = -1000; b <= 1000; ++b)
            {
                uint32_t n = 0;
                bool bIsPrime = true;

                // As long as primes are found, continue computing
                while (bIsPrime)
                {
                    int32_t p = n * n + a * n + b;

                    bIsPrime = !!bvSieve[std::abs(p)];
                    ++n;
                }
                --n;

                if(n > maxNumPrime)
                {
                    maxNumPrime = n;
                    result = a * b;
                }
            }
        }

       SetAnswer(result);
    }

}

#include "Problem0041.h"
#include "Libs\EratosthenesSieve.h"
#include "Libs\EulerMath.h"

namespace Euler {

    /**
     * Problem: Pandigital prime
     *
     * We shall say that an n-digit number is pandigital if it makes use of
     * all the digits 1 to n exactly once. For example, 2143 is a 4-digit
     * pandigital and is also prime.
     *
     * What is the largest n-digit pandigital prime that exists?
     */
    void Problem41::Solve()
    {
        uint32_t result = 0;

        // We need an upper-bound because primes <= 987654321 are too long
        // to compute. We need to apply the divisibility rules of digit sum
        // to eliminate the largest numbers., until it does not satisfy any
        // divisibility rules involving digits in any order.
        //   9-digits = 9+8+7+6+5+4+3+2+1 = 45 -> Divisible by 3 rule
        //   8-digits =   8+7+6+5+4+3+2+1 = 36 -> Divisible by 3 rule
        //   7-digits =     7+6+5+4+3+2+1 = 28 -> No rule
        const uint32_t kLimit = 7654321;
        EulerLib::EratosthenesSieve sieve(kLimit);
        EulerLib::PrimeSieve::Primes vPrimes;

        sieve(vPrimes, kLimit);

        // We will just brute-force through all primes and verify if is a
        // pandigital number
        size_t primesSize = vPrimes.size();

        for (size_t i = 0; i < primesSize; ++i)
        {
            uint32_t numDigits = EulerLib::CountDigits(vPrimes[i]);

            if (EulerLib::IsPandigital(vPrimes[i], numDigits))
            {
                result = vPrimes[i];
            }
        }

        SetAnswer(result);
    }
}
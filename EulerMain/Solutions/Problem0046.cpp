#include "Problem0046.h"
#include "Libs\EulerMath.h"
#include "Libs\EratosthenesSieve.h"

namespace Euler {

    /**
     * Problem: Goldbach's other conjecture
     *
     * It was proposed by Christian Goldbach that every odd composite number
     * can be written as the sum of a prime and twice a square.
     *
     *  9 =  7 + 2×1**2
     * 15 =  7 + 2×2**2
     * 21 =  3 + 2×3**2
     * 25 =  7 + 2×3**2
     * 27 = 19 + 2×2**2
     * 33 = 31 + 2×1**2
     * 
     * It turns out that the conjecture was false.
     * 
     * What is the smallest odd composite that cannot be written as the sum of
     * a prime and twice a square?
     */
    void Problem46::Solve()
    {
        uint32_t result = 0;

        // We know how to generate prime number, so we will get some until
        // a certain bound
        EulerLib::EratosthenesSieve sieve;
        EulerLib::PrimeSieve::Primes vPrimes;

        sieve(vPrimes, 10000);

        // Compute odd composite numbers
        std::vector<uint32_t> composite_odd;

        for (uint32_t i = 0; i < (vPrimes.size() - 1); i++)
        {
            // Composite numbers are in range ]prime_(x), prime_(x+1)[
            for (uint32_t j = vPrimes[i] + 1; j < vPrimes[i+1]; ++j)
            {
                // Odd composite?
                if ((j & 0x1) == 1)
                {
                    composite_odd.push_back(j);
                }
            }
        }

        // Let n be composite and odd, and let p be prime:
        //    n = p + 2m**2
        // We can isolate m:
        //    m = sqrt((n - p) / 2)
        // In turn, it sets the following conditions:
        //   1. m > 0
        //   2. (n - p) / 2 implies |n - p| is even, so prime 2 is rejected
        //   3. (n - p) > 1, because m > 0, n = p is invalid and n is composite odd
        //                  and prime 2 is rejected, so prime are all odd.
        //   4. if (n - p)/2 is a perfect square, we have a solution
        for (uint32_t c = 0; c < composite_odd.size(); ++c)
        {

            uint32_t composite = composite_odd[c];
            uint32_t index = 1;
            uint32_t prime = vPrimes[index]; // No even prime, 2 is rejected, this index 1
            uint32_t upper_bound = composite - 1;

            while (prime < upper_bound && index < (vPrimes.size() - 1))
            {
                // Only test for perfect square
                double t = static_cast<double>((composite - prime) >> 1);
                double m = EulerLib::SquareRoot(t);

                if (m == EulerLib::Round(m))
                {
                    break;
                }
                else
                {
                    prime = vPrimes[++index];
                }
            }

            if (prime >= upper_bound)
            {
                result = composite;
                break;
            }
        }

        SetAnswer(result);
    }
}
#include "Problem0004.h"
#include "Libs/EulerMath.h"

namespace Euler {

    /**
     * Problem: Largest palindrome product
     *
     * A palindromic number reads the same both ways. The largest palindrome made
     * from the product of two 2-digit numbers is 9009 = 91 × 99.
     *
     * Find the largest palindrome made from the product of two 3-digit numbers.
     */
    void Problem4::Solve()
    {
        const uint32_t kHigh = 999;
        const uint32_t kLow  = 100;
        const uint32_t kUpperBound = kHigh * kHigh;
        const uint32_t kLowerBound = kLow * kLow;

        bool     bFound = false;
        uint64_t result = 0;

        // Search the greatest palindrom factors below 1,000,000.
        for (uint32_t n = kUpperBound; n >= kLowerBound && !bFound; --n)
        {
            if (EulerLib::IsPalindromic(n, 10))
            {
                for (uint32_t a = kHigh; a >= kLow && !bFound; --a)
                {
                    uint32_t b = n / a;

                    if ((n % a) == 0 && b >= kLow && b < (kHigh + 1))
                    {
                        result = a * b;
                        bFound = true;
                    }
                }
            }
        }

        SetAnswer(result);
    }
}
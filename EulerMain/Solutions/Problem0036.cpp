#include "Problem0036.h"
#include "Libs/EulerMath.h"

namespace Euler {

    /**
     * Problem: Double-base palindromes
     *
     * The decimal number, 585 = 1001001001b (binary), is palindromic in both
     * bases.
     *
     * Find the sum of all numbers, less than one million, which are
     * palindromic in base 10 and base 2.
     *
     * (Please note that the palindromic number, in either base, may not include
     * leading zeros.)
     */
    void Problem36::Solve()
    {
        const uint32_t kLimit = 1000000;
        uint32_t result = 0;

        for (uint32_t i = 0; i < kLimit; ++i)
        {
            // Check base 10 and 2 is palindrom
            if (EulerLib::IsPalindromic(i, 10) &&
                EulerLib::IsPalindromic(i, 2))
            {
                result += i;
            }
        }

        SetAnswer(result);
    }
}
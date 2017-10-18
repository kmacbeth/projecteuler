#include "Problem0034.h"
#include "Libs/EulerMath.h"

namespace Euler {

    /**
     * Problem: Digit factorials
     *
     * 145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
     *
     * Find the sum of all numbers which are equal to the sum of the 
     * factorial of their digits.
     *
     * Note: as 1! = 1 and 2! = 2 are not sums they are not included.
     */
    void Problem34::Solve()
    {
        // We are asked to determine factorions.
        // Reference: https://en.wikipedia.org/wiki/Factorion

        // We need to define an upper bound to our search. We must check
        // for a values n which are greater or equal to the smallest number
        // with the same number of digits as n and which is smaller or equal
        // to the sum of eac digits factorial for the largest digit value 9.
        // So, for 1-digit:     1 <= n <= 9!       = 1*9! =  362880
        //     for 2-digit:    10 <= n <= 9!+9!    = 2*9! =  725760
        //     for 3-digit:   100 <= n <= 9!+9!+9! = 3*9! = 1088640
        // We can deduce that the numbers most satisfy the equation:
        //               10^(d-1) <= n <= d*9!
        // If we continue doing this until the equation is not satisfy, we
        // will find an upper bound:
        //     for 7-digit:  1000000 <= n <= 7*9! = 2540160
        //     for 8-digit: 10000000 <= n <= 8*9! = 2903040 -> Which is FALSE
        // So n <= 7*9!
        //
        // Now 7*9! = 2540160, the last digit can only be 0, 1 or 2, and the
        // others can be 9, we check that the sum of 2! + 6*9! return a 2 at
        // the highest digit:
        //     2! + 6*9! = 2177282 which is smaller, yield a new upper bound
        // Repeat with second highest digit:
        //     2! + 1! + 5*9! = 1814403, which is a contraction, so now we
        //     know that the new upper can be at most 1999999.
        const uint32_t kUpperBound = 1999999;
        const uint32_t kLowerBound = 3; // We cannot count 1 = 1! and 2 = 2!
        uint32_t result = 0;

        // Computing the factorial of is an expensive operator as for n! we
        // need to do (n - 1) multiply operations. We will only need
        // factorial up to 9!, we need to compute combinations of n! for 
        // n = {1, 2, 3, ..., 9} for around 1999999 numbers, which will require
        // between 2 to 7 factorials per numbers based on the digit value.
        // Since it requires a huge amount of factorial, we can precomputed
        // in an array at very low memory cost and very fast access (and
        // the array will be loaded in a cache line of the CPU which will
        // garantee almost instantaneous access).
        const uint32_t kNumFactorial = 10;
        std::vector<uint32_t> factorials(kNumFactorial);

        factorials[0] = 1;
        for (uint32_t f = 1; f < kNumFactorial; ++f)
        {
            factorials[f] = factorials[f-1] * f;
        }
    
        // Compute the factorion for each numbers.
        for (uint32_t number = kLowerBound; number <= kUpperBound; ++number)
        {
            uint32_t n = number;
            uint32_t sum = 0;

            // Get factorial from each digit and accumulate sum
            while (n > 0)
            {
                sum += factorials[n % 10];
                n /= 10;
            }

            // Test if factorion
            if (sum == number)
            {
                result += number;
            }
        }

        SetAnswer(result);
    }
}
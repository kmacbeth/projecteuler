#include "Problem0023.h"
#include "Libs/DivisorFunction.h"

namespace Euler {

    /**
     * Problem: Non-abundant sums
     *
     * A perfect number is a number for which the sum of its proper divisors is
     * exactly equal to the number. For example, the sum of the proper divisors
     * of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect
     * number.
     *
     * A number n is called deficient if the sum of its proper divisors is less
     * than n and it is called abundant if this sum exceeds n.
     *
     * As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest
     * number that can be written as the sum of two abundant numbers is 24. By
     * mathematical analysis, it can be shown that all integers greater than 28123
     * can be written as the sum of two abundant numbers. However, this upper limit
     * cannot be reduced any further by analysis even though it is known that the
     * greatest number that cannot be expressed as the sum of two abundant numbers
     * is less than this limit.
     *
     * Find the sum of all the positive integers which cannot be written as the sum
     * of two abundant numbers.
     */
    void Problem23::Solve()
    {
        const uint32_t kStartingNumber = 12;
        const uint32_t kLimit = 28124;
        const uint32_t kHalfLimit = kLimit / 2;

        EulerLib::DivisorFunction divisorFunc;

        // Find all abundant number starting at 12 and ending at 28123
        std::vector<uint32_t> vAbundantNumbers;

        for (uint32_t n = kStartingNumber; n < kLimit; ++n)
        {
            // Check abundance: d(n) - n > n => d(n) > 2n
            if (divisorFunc(n, 1) > (n << 1))
            {
                vAbundantNumbers.push_back(n);
            }
        }

        // Find all abundant sum
        std::vector<uint8_t> bIsAbundantSum(kLimit, 0);
        size_t abundantNumbersSize = vAbundantNumbers.size();

        // We stop at half the limit otherwise we will sum two numbers
        // greater or equal to half the limit, hence we would overflow the
        // limit.
        for (size_t p = 0; vAbundantNumbers[p] < kHalfLimit; ++p)
        {
            // To avoid computing twice the sum of the same pair of
            // numbers, we start this index at index p.
            uint32_t sum = 0;

            for (size_t q = p; q < abundantNumbersSize && sum < kLimit; ++q)
            {
                sum = vAbundantNumbers[p] + vAbundantNumbers[q];

                if (sum < kLimit)
                {
                    bIsAbundantSum[sum] = 1;
                }
            }
        }

        // Now that we now all abundant sum, we can deduce number
        // that cannot be made by combinin two abundant numbers.
        uint32_t result = 0;
        size_t adundantSumSize = bIsAbundantSum.size();

        for (size_t n = 0; n < adundantSumSize; ++n)
        {
            if (!bIsAbundantSum[n])
            {
                result += n;
            }
        }

        SetAnswer(result);
    }

}

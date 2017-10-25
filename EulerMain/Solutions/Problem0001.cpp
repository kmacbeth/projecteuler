#include "Problem0001.h"

namespace Euler {

    /**
     * Problem: Multiples of 3 and 5
     *
     * If we list all the natural numbers below 10 that are multiples of 3 or 5,
     * we get 3, 5, 6 and 9. The sum of these multiples is 23.
     *
     * Find the sum of all the multiples of 3 or 5 below 1000.
     */
    void Problem1::Solve()
    {
        const uint32_t kLimit = 1000;
        uint64_t result = 0;

        // Sum all multiple of 3 and 5, but remove once the common ones.
        result = SumMultipleOfAKind( 3, kLimit) +
                 SumMultipleOfAKind( 5, kLimit) -
                 SumMultipleOfAKind(15, kLimit);

        SetAnswer(result);
    }

    /**
     * Find multiples of a kind under a certain limit.
     *
     * @param a_Mult  Multiple of a kind
     * @param a_Limit Upper limit when to stop looking fro multiple of a kind
     *
     * @return Sum of all the multiple of a kind found.
     */
    uint32_t Problem1::SumMultipleOfAKind(uint32_t a_Kind, uint32_t a_Limit)
    {
        uint32_t sum = 0;
        uint32_t number = 0;

        while((number + a_Kind) < a_Limit)
        {
            number += a_Kind;
            sum += number;
        }

        return sum;
    }

}
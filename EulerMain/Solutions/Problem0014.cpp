#include "Problem0014.h"

namespace Euler {

    /**
     * Problem: Longest Collatz sequence
     *
     * The following iterative sequence is defined for the set of positive 
     * integers:
     *
     *              n → n/2 (n is even)
     *              n → 3n + 1 (n is odd)
     *
     * Using the rule above and starting with 13, we generate the following 
     * sequence:
     *
     *                  13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
     *
     * It can be seen that this sequence (starting at 13 and finishing at 1) 
     * contains 10 terms. Although it has not been proved yet (Collatz Problem), 
     * it is thought that all starting numbers finish at 1.
     *
     * Which starting number, under one million, produces the longest chain?
     *
     * NOTE: Once the chain starts the terms are allowed to go above one million.
     */
    void Problem14::Solve()
    {
        const uint32_t kLimit = 1000000;
        uint32_t longestChain = 0;
        uint32_t result = 0;

        for (uint32_t n = 13; n < kLimit; ++n)
        {
            uint32_t chainCount = 1;
            uint32_t number = n;

            while (number > 1)
            {
                if ((number & 0x1) == 0)
                {
                    number /= 2;
                }
                else
                {
                    number = 3 * number + 1;
                }
                chainCount++;
            }

            if (chainCount > longestChain)
            {
                longestChain = chainCount;
                result = n;
            }
        }

        SetAnswer(result);
    }

}

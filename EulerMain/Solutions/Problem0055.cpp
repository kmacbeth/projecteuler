#include "Problem0055.h"
#include "Libs\EulerMath.h"
#include "Libs\BigInteger.h"

namespace Euler {

    /**
     * Problem: Lychrel numbers
     *
     * If we take 47, reverse and add, 47 + 74 = 121, which is palindromic.
     *
     * Not all numbers produce palindromes so quickly. For example,
     *
     *       349 + 943 = 1292,
     *      1292 + 2921 = 4213
     *      4213 + 3124 = 7337
     *
     * That is, 349 took three iterations to arrive at a palindrome.
     *
     * Although no one has proved it yet, it is thought that some numbers,
     * like 196, never produce a palindrome. A number that never forms a
     * palindrome through the reverse and add process is called a Lychrel
     * number. Due to the theoretical nature of these numbers, and for the
     * purpose of this problem, we shall assume that a number is Lychrel until
     * proven otherwise. In addition you are given that for every number below
     * ten-thousand, it will either (i) become a palindrome in less than fifty
     * iterations, or, (ii) no one, with all the computing power that exists,
     * has managed so far to map it to a palindrome. In fact, 10677 is the first
     * number to be shown to require over fifty iterations before producing a
     * palindrome: 4668731596684224866951378664 (53 iterations, 28-digits).
     *
     * Surprisingly, there are palindromic numbers that are themselves Lychrel numbers; the first example is 4994.
     *
     * How many Lychrel numbers are there below ten-thousand?
     */
    void Problem55::Solve()
    {
        const uint32_t kUpperLimit = 10000;
        const uint32_t kLowerLimit = 10;
        const uint32_t kMaxIterations = 50;
        uint64_t a = 0;
        uint64_t b = 0;
        uint32_t result = 0;

        // We will not generate number > 2**64-1, so its ok to use uint64_t
        for (uint32_t n = kLowerLimit; n < kUpperLimit; ++n)
        {
            uint64_t a = n;
            uint64_t b = EulerLib::Reverse(a);

            for (uint32_t i = 0; i < kMaxIterations; ++i)
            {
                a += b;
                b = EulerLib::Reverse(a);

                if (a == b)
                {
                    break;
                }
            }
            if (a != b)
            {
                ++result;
            }
        }

        SetAnswer(result);
    }
}
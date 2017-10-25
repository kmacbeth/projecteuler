#include "Problem0026.h"

namespace Euler {

    /**
     * Problem: Reciprocal cycles
     *
     * A unit fraction contains 1 in the numerator. The decimal representation
     * of the unit fractions with denominators 2 to 10 are given:
     *
     *     1/2  =   0.5
     *     1/3  =   0.(3)
     *     1/4  =   0.25
     *     1/5  =   0.2
     *     1/6  =   0.1(6)
     *     1/7  =   0.(142857)
     *     1/8  =   0.125
     *     1/9  =   0.(1)
     *     1/10 =   0.1
     *
     * Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can
     * be seen that 1/7 has a 6-digit recurring cycle.
     *
     * Find the value of d < 1000 for which 1/d contains the longest recurring
     * cycle in its decimal fraction part.
     */
    void Problem26::Solve()
    {
        // Brute force solution
        uint32_t maxCycleLength = 0;
        uint32_t result = 999;

        // Cycle length always smaller than number value
        for (uint32_t number = 999; number > 1; --number)
        {
            // So, if we reached the number with less than or equal to the
            // greatest cycle length, we know we have previously found the
            // greatest cycle.
            if (number <= maxCycleLength)
            {
                result = number + 1;
                break;
            }

            // For each remainder we keep the first position in the decimal
            // digits that we encounter it. When we encounter the remainder
            // again, it means we reach the end of the cycle.
            std::vector<uint32_t> vRemainders(result, 0);
            // Since we always do 1/N, first remainder is always 1
            uint32_t remainder = 1;
            uint32_t position = 0;

            // Sort of a long division, keeping track of the remainder only
            // at each decimal digit. Computing the digits themselves is not
            // required.
            while (vRemainders[remainder] == 0)
            {
                vRemainders[remainder] = position;
                remainder *= 10;
                remainder %= number;
                ++position;
            }

            // We encounter the remainder again, we compute the cycle
            // by subtracting this remainder last position from the
            // current one.
            uint32_t cycleLength = position - vRemainders[remainder];

            if (cycleLength > maxCycleLength)
            {
                maxCycleLength = cycleLength;
            }
        }

        SetAnswer(result);
    }
}
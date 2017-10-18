#include "Problem0052.h"
#include "Libs\EulerMath.h"

namespace Euler {

    /**
     * Problem: Permuted multiples
     *
     * It can be seen that the number, 125874, and its double, 251748, contain
     * exactly the same digits, but in a different order.
     *
     * Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, 
     * contain the same digits.
     */
    void Problem52::Solve()
    {
        uint32_t result = 0;
        
        uint32_t s = 10000;
        uint32_t t = 16666;
        uint32_t x = s;

        // We must have x # of digits = 6x # of digits,
        // So we need to test on a range of values of each n-digit numbers.
        // E.g.: [10000,16666]

        while (true)
        {
            const uint32_t num_xdigits = EulerLib::CountDigits(x);

            // Check multipliers
            uint32_t mul = 0;

            for (mul = 2; mul < 7; ++mul)
            {
                uint32_t value = mul * x;

                if (!DoesDigitsOccurenceEqual(x, value))
                {
                    break;
                }
            }

            // found when mul reached 7
            if (mul == 7)
            {
                result = x;
                break;
            }

            // Adjust x by range [s, t] = [x0...0, x6...6]
            if (x == t)
            {
                s *= 10;
                t *= 10;
                t +=  6;
                x = s;
            }
            else
            {
                ++x;
            }
        }

        SetAnswer(result);
    }

    /**
     * Verify digits occurence is equal between two numbers
     *
     * @param a Reference number
     * @param b Tested number
     *
     * @return Whether both number are equal or not.
     */
    bool Problem52::DoesDigitsOccurenceEqual(uint64_t a, uint64_t b)
    {
        uint32_t a_digits[10] = { 0 };
        uint32_t b_digits[10] = { 0 };

        while (a > 0)
        {
            a_digits[a % 10]++;
            a /= 10;
        }

        while (b > 0)
        {
            b_digits[b % 10]++;
            b /= 10;
        }

        for (uint32_t i = 0; i < 10; ++i)
        {
            if (a_digits[i] != b_digits[i])
            {
                return false;
            }
        }
        return true;
    }

}
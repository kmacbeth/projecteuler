#include "Problem0030.h"
#include "Libs/EulerMath.h"

namespace Euler {

    /**
     * Problem: Digit fifth powers
     *
     * Surprisingly there are only three numbers that can be written as the sum
     * of fourth powers of their digits:
     *
     *      1634 = 1^4 + 6^4 + 3^4 + 4^4
     *      8208 = 8^4 + 2^4 + 0^4 + 8^4
     *      9474 = 9^4 + 4^4 + 7^4 + 4^4
     *
     * As 1 = 1^4 is not a sum it is not included.
     * The sum of these numbers is 1634 + 8208 + 9474 = 19316.
     *
     * Find the sum of all the numbers that can be written as the sum of fifth
     * powers of their digits.
     */
    void Problem30::Solve()
    {       
        // We need to find a lower bound and an upper bound to our search.
        // Our smallest single digit is 0 and we need at least 2 digits, so
        // we can start at 10.
        //
        // The largest single digit is 9. 9^5 = 59049, so the upper bound is
        // at least a 5-digit number. Need need to check for a 5-digit number
        // how many digit can be generate at maximum. This is for 99999:
        //    9^5 + 9^5 + 9^5 + 9^5 + 9^5 = 5*9^5 = 295245
        // Okay, we've got 6-digit, so we need to verify if for a 6-digit
        // numbers we can generate a greater number of digits:
        //    6*9^5 = 354294
        // Thats' the greatest number we can generate from 6-digits. That's
        // the upper bound.
        const uint32_t kLowerBound = 10;
        const uint32_t kUpperBound = 354295; // +1
        uint32_t result = 0;

        for (uint32_t number = kLowerBound; number < kUpperBound; number++)
        {
            uint32_t digits = number;
            uint32_t sum = 0;

            // Sum of fifth powers
            while (digits > 0)
            {
                sum += EulerLib::Power(digits % 10, 5);
                digits /= 10;
            }

            if (number == sum)
            {
                result += number;
            }
        }

        SetAnswer(result);
    }
}
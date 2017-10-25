#include "Problem0040.h"
#include "Libs\EulerMath.h"

namespace Euler {

    /**
     * Problem: Champernowne's constant
     *
     * An irrational decimal fraction is created by concatenating the
     * positive integers:
     *
     * 0.123456789101112131415161718192021...
     *
     * It can be seen that the 12th digit of the fractional part is 1.
     *
     * If dn represents the nth digit of the fractional part, find the
     * value of the following expression.
     *
     * d1 × d10 × d100 × d1000 × d10000 × d100000 × d1000000
     */
    void Problem40::Solve()
    {
        // Will break out of loop with a number at most 6-digits
        const uint32_t kMaxDigits = 1000000 + 6;
        const uint32_t kMaxNumber = 185185;


        std::vector<uint32_t> vDigits(kMaxDigits, 0);
        uint32_t numberIndex = 0;

        // We will just push each digit of every number into the array
        // We have the 1 millionth digit at number 185185 because,
        //       9 * 1 digit
        // +    90 * 2-digit
        // +   900 * 3-digit
        // +  9000 * 4-digit
        // + 90000 * 5-digit
        // + 85186 * 6-digit
        // = 1000000 digits
        for (uint32_t i = 1; i <= kMaxNumber && numberIndex < kMaxDigits; ++i)
        {
            uint32_t numDigits = EulerLib::CountDigits(i);
            uint32_t digitIndex = numDigits;
            uint32_t divider = 1;

            while (digitIndex > 0)
            {
                // Add digit from right to left of the decimal, e.g.:
                //   adding 123 to 0.12345...122000
                //                 0.12345...122003
                //                 0.12345...122023
                //                 0.12345...122123
                vDigits[numberIndex + digitIndex - 1] = (i / divider) % 10;
                divider *= 10;
                --digitIndex;
            }

            numberIndex += numDigits;
        }

        // Multiply 1st, 10th, 100th, 1000th, 10000th, 100000th and 1000000th
        // digits.
        uint32_t result = 1;
        uint32_t decimalIndex = 1;

        while (decimalIndex <= kMaxDigits)
        {
            result *= static_cast<uint32_t>(vDigits[decimalIndex - 1]);
            decimalIndex *= 10;
        }

        SetAnswer(result);
    }
}

#include "Problem0020.h"
#include "Libs/BigInteger.h"

namespace Euler {

    /**
     * Problem: Factorial digit sum
     *
     * n! means n x (n − 1) x ... x 3 x 2 x 1
     *
     * For example, 10! = 10 x 9 x ... x 3 x 2 x 1 = 3628800,
     * and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.
     *
     * Find the sum of the digits in the number 100!
     */
    void Problem20::Solve()
    {
        const uint32_t factorial = 100;
        EulerLib::BigInteger bigNumber = 1;

        for (uint32_t n = 2; n <= factorial; ++n)
        {
            bigNumber *= n;
        }

        // Get an array of digit for the sum
        std::string digits = bigNumber.ToString();
        size_t numDigits = digits.size();
        uint64_t result = 0;

        for (size_t i = 0; i < numDigits; ++i)
        {
            result += ::atol(digits.substr(i, 1).c_str());
        }

        SetAnswer(result);
    }

}

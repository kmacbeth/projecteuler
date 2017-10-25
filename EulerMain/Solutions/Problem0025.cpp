#include "Problem0025.h"
#include "Libs/EulerMath.h"
#include "Libs/BigInteger.h"
#include "Libs/FibonacciSequence.h"

namespace Euler {

    /**
     * Problem: 1000-digit Fibonacci number
     *
     * The Fibonacci sequence is defined by the recurrence relation:
     *
     * Fn = Fn−1 + Fn−2, where F1 = 1 and F2 = 1.
     * Hence the first 12 terms will be:
     *
     * F1 = 1
     * F2 = 1
     * F3 = 2
     * F4 = 3
     * F5 = 5
     * F6 = 8
     * F7 = 13
     * F8 = 21
     * F9 = 34
     * F10 = 55
     * F11 = 89
     * F12 = 144
     * The 12th term, F12, is the first term to contain three digits.
     *
     * What is the index of the first term in the Fibonacci sequence to contain
     * 1000 digits?
     */
    void Problem25::Solve()
    {
        const uint32_t kNumDigits = 1000;

        // Compute the first 1000 digits number
        // It is faster to convert a single very long string to a BigInteger
        // than calling ToString every time we want to check the number of digits
        // from the current fibonacci number. It is also faster than using an algorithm
        // to check once in a while the number of digit by converging closer to the
        // researched number.
        std::string str1000Digits(1000, '0');

        str1000Digits[0] = '1';

        EulerLib::BigInteger k1000Digits(str1000Digits);

        // Initiate the Fibonacci sequence
        EulerLib::FibonacciSequence<EulerLib::BigInteger> fibonacci(1, 1);
        EulerLib::BigInteger bigFib;

        uint64_t index = 2;

        // This comparison is fast, since it is done on QWORDs directly
        while (bigFib < k1000Digits)
        {
            bigFib = fibonacci();
            ++index;
        }

        uint64_t result = index;

        SetAnswer(result);
    }

}
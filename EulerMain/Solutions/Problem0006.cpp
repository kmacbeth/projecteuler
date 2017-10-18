#include "Problem0006.h"

namespace Euler {

    /**
     * Problem: sum square difference
     *
     * The sum of the squares of the first ten natural numbers is,
     *
     *                1**2 + 2**2 + ... + 10**2 = 385
     * The square of the sum of the first ten natural numbers is,
     *
     *            (1 + 2 + ... + 10)**2 = 552 = 3025
     * 
     * Hence the difference between the sum of the squares of the first ten 
     * natural numbers and the square of the sum is 3025 − 385 = 2640.
     *
     * Find the difference between the sum of the squares of the first one 
     * hundred natural numbers and the square of the sum.
     */
    void Problem6::Solve()
    {
        uint64_t result = 0;
        uint64_t sumOfSquare = 0;
        uint64_t squareOfSum = 0;

        for(uint64_t n = 1; n < 101; ++n)
        {
            sumOfSquare += n * n;
            squareOfSum += n;
        }

        squareOfSum *= squareOfSum;

        result = squareOfSum - sumOfSquare;

        SetAnswer(result);
    }

}
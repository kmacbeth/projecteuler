#include "Problem0053.h"
#include "Libs\EulerMath.h"

namespace Euler {

    /**
     * Problem: Combinatoric selections
     *
     * There are exactly ten ways of selecting three from five, 12345:
     *
     * 123, 124, 125, 134, 135, 145, 234, 235, 245, and 345
     *
     * In combinatorics, we use the notation, 5^C_3 = 10.
     *
     * In general,
     *
     *  n^C_r =	n! / (r!(n−r)!), where r ≤ n, n! = n×(n−1)×...×3×2×1, and 0! = 1.
     *
     * It is not until n = 23, that a value exceeds one-million: 23^C_10 = 1144066.
     *
     * How many, not necessarily distinct, values of  nCr, for 1 ≤ n ≤ 100, are 
     * greater than one-million?
     */
    void Problem53::Solve()
    {
		const uint32_t kLowerBound = 1000000;
		const uint32_t kMinN = 1;
		const uint32_t kMaxN = 100;
        uint32_t result = 0;

        // We need to generate the Binomial Coefficients
        // For n = 5, C(1, r) = {1, 5, 10, 10, 5, 1} for r = 0..5
        // We basically need to find the first r where C(1, r) > 10**6
        // C(1,r) > 10**6 for [a, n-a]
        for (uint32_t n = kMinN; n <= kMaxN; ++n)
        {
            // Only search at most half + 1 coefficients
            uint32_t limit = (((n & 1) == 0 ? 2 : 1) + n) / 2;

            for (uint32_t r = 0; r <= limit; ++r)
            {
                if (EulerLib::GetBinomialCoefficient(n, r) >= kLowerBound)
                {
                    result += (n + 1) - (2 * r);
                    break;
                }
            }
        }

        SetAnswer(result);
    }
}
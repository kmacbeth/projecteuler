#include "Problem0039.h"
#include "Libs\EulerMath.h"

namespace Euler {

    /**
     * Problem: Integer right triangles
     *
     * If p is the perimeter of a right angle triangle with integral length
     * sides, {a,b,c}, there are exactly three solutions for p = 120.
     *
     * {20,48,52}, {24,45,51}, {30,40,50}
     *
     * For which value of p ≤ 1000, is the number of solutions maximised?
     */
    void Problem39::Solve()
    {
        uint32_t result = 0;

        // This is basically problem 9, but with multiple p to test.
        //            c**2 = a**2 + b**2 and p = a + b + c
        //  (p - a - b)**2 = a**2 + b**2
        // By simplification:
        //                  b = p(p/2 - a)/(p - a)
        // Using variable substitution n = p(p/2 - a) and m = (p - a),
        // we only need to satisfy (n mod m) = 0. Since we have a p/2 term,
        // p must be even.
        const uint32_t kMaxLimit = 1000;
        const uint32_t kMinLimit = 2;
        uint32_t largestNumberSolutions = 0;

        for (uint32_t p = kMinLimit; p <= kMaxLimit; p += 2)
        {
            uint32_t numSolutions = 0;

            for (uint32_t a = 1; a < (p >> 1); a++)
            {
                uint32_t n = p * ((p >> 1) - a);
                uint32_t m = p - a;

                if ((n % m) == 0)
                {
                    numSolutions++;
                }
            }

            if (numSolutions > largestNumberSolutions)
            {
                largestNumberSolutions = numSolutions;
                result = p;
            }
        }

        SetAnswer(result);
    }
}
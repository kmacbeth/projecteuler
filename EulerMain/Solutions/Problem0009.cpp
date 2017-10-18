#include "Problem0009.h"

namespace Euler {

    /**
     * Problem: Special Pythagorean triplet
     *
     * A Pythagorean triplet is a set of three natural numbers, a < b < c, 
     * for which,
     *
     *                          a**2 + b**2 = c**2
     * 
     * For example, 32 + 42 = 9 + 16 = 25 = 52.
     *
     * There exists exactly one Pythagorean triplet for which a + b + c = 1000.
     * Find the product abc.
     */
    void Problem9::Solve()
    {
        uint64_t result = 0;

        // Let c = N - a - b -> a**2 + b**2 = (N - a - b)**2
        //
        // By simplification, we can isolate b:
        //    
        //              b(1000 - a) = 1000(500 - a)
        // Thus
        //                        b = 1000(500 - a) / (1000 - a)
        //
        // However, we only need to do the following variable substitution
        // and verify the modulo to make sure b is a natural number:
        //
        //        m = (1000 - a) and n = (500 - a) => bm = n
        //        n (mod m) = 0  =>  found solution
        //       
        const uint32_t N = 1000;

        uint32_t a = 0;
        uint32_t b = 0;
        uint32_t c = 0;

        uint32_t m = 0;
        uint32_t n = 0;

        for(a = 1; a < N/2; ++a)
        {
            m = N - a;
            n = N * (N / 2 - a);

            if(n % m == 0)
            {
                break;
            }
        }

        b = n / m;
        c = N - a - b;

        result = a * b * c;

        SetAnswer(result);
    }

}
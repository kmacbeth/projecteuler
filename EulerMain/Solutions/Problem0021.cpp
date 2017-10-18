#include "Problem0021.h"
#include "Libs/DivisorFunction.h"

namespace Euler {

    /**
     * Problem: Amicable numbers
     *
     * Let d(n) be defined as the sum of proper divisors of n (numbers less than n 
     * which divide evenly into n). If d(a) = b and d(b) = a, where a ≠ b, then a 
     * and b are an amicable pair and each of a and b are called amicable numbers.
     *
     * For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 
     * 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 
     * 71 and 142; so d(284) = 220.
     *
     * Evaluate the sum of all the amicable numbers under 10000.
     */
    void Problem21::Solve()
    {
        EulerLib::DivisorFunction divisorFunc;
        std::map<uint64_t, uint64_t> mProperSum;
        uint64_t result = 0;

        for (uint32_t n = 4; n < 10000; ++n)
        {
            // Find all proper divisor and sum
            uint64_t sum = divisorFunc(n, 1) - n;

            mProperSum[n] = sum; 

            // Check amicability. If sum not in map, it adds key with value zero,
            // which is not an amicable number. It can later be updated if n 
            // reached sum value.
            if (mProperSum[sum] == n && sum != n)
            {
                result += (n + sum);
            }                   
        }
    
        SetAnswer(result);
    }

}

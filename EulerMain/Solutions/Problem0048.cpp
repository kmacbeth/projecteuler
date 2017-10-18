#include "Problem0048.h"
#include "Libs\EulerMath.h"
#include "Libs\ModularArith.h"

namespace Euler {

    /**
     * Problem: Self powers
     *
     * The series, 1**1 + 2**2 + 3**3 + ... + 10**10 = 10405071317.
     *
     * Find the last ten digits of the series, 
     *      1**1 + 2**2 + 3**3 + ... + 10001000.
     */
    void Problem48::Solve()
    {
        int64_t result = 0;
     
        // This a problem of modular arithmetic. We are only interested in the
        // remainder of the solution, since only the last ten digits are 
        // needed. 
        const int64_t kDivider = 10000000000;
        
        for (uint32_t n = 1; n < 1001; ++n)
        {
            uint64_t value = EulerLib::Modular::Pow(n, n, kDivider);

            result = EulerLib::Modular::Add(result, value, kDivider);
        }  
        
        SetAnswer(result);
    }
}
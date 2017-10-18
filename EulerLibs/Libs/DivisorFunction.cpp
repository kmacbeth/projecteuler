#include "EulerMath.h"
#include "PrimeFactorizer.h"
#include "DivisorFunction.h"

namespace EulerLib {

    /**
     * The divisor function. 
     * 
     * The zeroth power compute the number of divisors.
     * The forst power compute the sum of the of all positive divisor.
     * Others powers are not computed and return zero.
     *
     * Example: 
     *    Sigma(6, 0) = 4 = (1 + 1)(1 + 1);
     *    Sigma(6, 1) = 1 + 2 + 3 + 6 = sigma(2**1) * sigma(3**1)
     *
     * @param a_Number   Number for which we apply the divisor function.
     * @param a_KthPower Which k power to apply.
     *
     * @return Returns the results for either zeroth or first power.
     */
    uint64_t DivisorFunction::operator() (uint64_t a_Number, uint32_t a_KthPower)
    {
        // Find prime factorization of number
        PrimeFactorizer::FactorList factors;
        PrimeFactorizer factorize;
        
        factorize(a_Number, factors);

        // Reference: http://mathschallenge.net/library/number/sum_of_divisors
        uint32_t numFactors = factors.size();

        if (a_KthPower == 1)
        {
            uint64_t divisorSum = 1; 

            for (uint32_t i = 0; i < numFactors; ++i)
            {
                uint64_t primePower = 1;

                // sigma(p**n) = (p**(n+1) - 1)/(p - 1)
                for(uint32_t e = 0; e <= factors[i].m_Exponent; ++e)
                {
                    primePower *= factors[i].m_Base;
                }

                divisorSum *= (primePower - 1) / (factors[i].m_Base - 1);
            }

            return divisorSum;
        }
        else if (a_KthPower == 0)
        {
            uint64_t divisorCount = 1;

            for (uint32_t i = 0; i < numFactors; ++i)
            {
                divisorCount *= (factors[i].m_Exponent + 1);
            }

            return divisorCount;
        }

        return 0;
    }

}

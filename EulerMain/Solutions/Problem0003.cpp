#include "Problem0003.h"
#include "Libs/PrimeFactorizer.h"

namespace Euler {

    /**
     * Problem: Largest prime factor
     *
     * The prime factors of 13195 are 5, 7, 13 and 29.
     *
     * What is the largest prime factor of the number 600851475143 ?
     */
    void Problem3::Solve()
    {
        const uint64_t kNumber = 600851475143ull;
        uint64_t result = 0;

        EulerLib::PrimeFactorizer::FactorList vFactors;
        EulerLib::PrimeFactorizer factorize;

        factorize(kNumber, vFactors);

        // factors are always ordered ascending, so largest prime
        // is the last element.
        result = vFactors.back().m_Base;

        SetAnswer(result);
    }

}
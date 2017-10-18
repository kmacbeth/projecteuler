#include "PrimeCounter.h"
#include "EulerMath.h"

namespace EulerLib {

    /**
     * Estimate the number of primes below an integer number.
     *
     * Equation: Pi(x) = x / (ln(x) - 1)
     *
     * Reference: https://primes.utm.edu/howmany.html
     */
    uint64_t PrimeCounter::operator()(uint64_t limit)
    {
        double n = static_cast<double>(limit);
        double result = 0.0;

        result = EulerLib::Round(n / (std::log(n) - 1));

        return static_cast<uint64_t>(result);
    }

}
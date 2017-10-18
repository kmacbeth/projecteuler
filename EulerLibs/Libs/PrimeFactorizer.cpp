#include "PrimeFactorizer.h"
#include "EulerMath.h"

namespace EulerLib {

    /**
     * Prime factor default constructor.
     */
    PrimeFactorizer::Factor::Factor() :
        m_Base(0),
        m_Exponent(0)
    {
    }

    /**
     * Prime factor constructor.
     *
     * @param a_Base     Prime factor base.
     * @param a_Expoennt Prime factor exponent.
     */
    PrimeFactorizer::Factor::Factor(uint64_t a_Base, uint32_t a_Exponent) :
        m_Base(a_Base),
        m_Exponent(a_Exponent)
    {
    }

    /**
     * Default constructor.
     */
    PrimeFactorizer::PrimeFactorizer()
    {
    }

    /**
     * Generate all prime factors. Factors are non-unique, i.e. the same prime
     * can be list twice or more.
     *
     * Reference: https://en.wikipedia.org/wiki/Trial_division
     */
    void PrimeFactorizer::operator()(uint64_t a_Number, FactorList& a_rFactorList)
    {
        //std::vector<uint64_t> factors;
        uint64_t number = a_Number;
        uint64_t n = 2;

        a_rFactorList.clear();

        if (number == 1)
        {
            return;
        }

        // Find all factor with trial by division (slow)
        // Start by eliminating small primes factors, with will automatically
        // eliminate any composite factors.
        Factor primeFactor(0, 0);
        uint32_t count = 0;

        while (number != n)
        {
            if (number % n == 0)
            {
                number /= n;
                ++count;
            }
            else
            {
                if (count > 0)
                {
                    primeFactor.m_Base = n;
                    primeFactor.m_Exponent = count;

                    a_rFactorList.push_back(primeFactor);
                }

                count = 0;
                n += (n > 2 ? 2 : 1);
            }
        }

        if (number > 1)
        {
            primeFactor.m_Base = number;
            primeFactor.m_Exponent = ++count;

            a_rFactorList.push_back(primeFactor);
        }
    }

}
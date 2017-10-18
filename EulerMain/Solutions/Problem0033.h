#ifndef __EULER_PROBLEM33_H__
#define __EULER_PROBLEM33_H__

#include "Problem.h"
#include "Libs/Euler.h"

namespace Euler {

    class Problem33 : public Problem {

    public:
        Problem33() : Problem("Problem 33") {}
        
        void Solve();

    private:
        struct Fraction {
            uint32_t m_Numerator;
            uint32_t m_Denominator;

            Fraction(uint32_t a_Numerator, uint32_t a_Denominator) :
                m_Numerator(a_Numerator),
                m_Denominator(a_Denominator)
            {}
        };
        typedef std::vector<Fraction> FractionList;
        
        void FindEqualFractions(uint32_t a_Numerator, 
                                uint32_t a_Denominator, 
                                uint32_t a_NumeratorDigit, 
                                uint32_t a_DenominatorDigit, 
                                FractionList& a_rvFractions);
    };

}

#endif // __EULER_PROBLEM33_H__
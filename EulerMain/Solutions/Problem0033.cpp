#include "Problem0033.h"
#include "Libs\EulerMath.h"

namespace Euler {

    /**
     * Problem: Digit cancelling fractions
     *
     * The fraction 49/98 is a curious fraction, as an inexperienced 
     * mathematician in attempting to simplify it may incorrectly believe
     * that 49/98 = 4/8, which is correct, is obtained by cancelling the 9s.
     *
     * We shall consider fractions like, 30/50 = 3/5, to be trivial examples.
     *
     * There are exactly four non-trivial examples of this type of fraction,
     * less than one in value, and containing two digits in the numerator and 
     * denominator.
     *
     * If the product of these four fractions is given in its lowest common 
     * terms, find the value of the denominator.
     */
    void Problem33::Solve()
    {
        const uint32_t kMaxNumber = 99;
        uint32_t result = 0;
        FractionList fractions;

        // Generate each fraction. We must remember that denominator > numerator,
        // otherwise it will be greater than one.
        for (uint32_t numerator = 10; numerator < kMaxNumber; ++numerator)
        {
            for (uint32_t denominator = numerator + 1; 
                 denominator <= kMaxNumber; ++denominator)
            {
                uint32_t numeratorDigitUnit = numerator % 10;
                uint32_t numeratorDigitTens = numerator / 10;
                uint32_t denominatorDigitUnit = denominator % 10;
                uint32_t denominatorDigitTens = denominator / 10;

                // We know that n/d < 1 and so if the digit fraction a/b >= 1,
                // we cannot generate a fraction with the same value.
                if (numeratorDigitTens == denominatorDigitUnit && 
                    numeratorDigitUnit < denominatorDigitTens)
                {
                    FindEqualFractions(numerator, denominator, 
                                       numeratorDigitUnit, denominatorDigitTens, fractions);
                }
                else if (numeratorDigitUnit == denominatorDigitTens && 
                         numeratorDigitTens < denominatorDigitUnit)
                {
                    FindEqualFractions(numerator, denominator, 
                                       numeratorDigitTens, denominatorDigitUnit, fractions);
                } 
            }
        }

        // Compute product of all fractions in lower common denominator
        uint32_t productNumerator = 1;
        uint32_t productDenominator = 1;

        // We compute a fraction, were the numerator and denominator keep
        // increasing as we multiply. Once the multiplication is done, we
        // can simplify the fraction
        for (uint32_t i = 0; i < fractions.size(); ++i)
        {
            productNumerator   *= fractions[i].m_Numerator;
            productDenominator *= fractions[i].m_Denominator;
        }

        // For the result, we only need to simplify the denominator
        result = productDenominator / 
                 EulerLib::GCD(productNumerator, productDenominator);

        SetAnswer(result);
    }

    /**
     * Find equal fractions.
     *
     * @param a_Numerator        Fraction numerator.
     * @param a_Denominator      Fraction denominator.
     * @param a_NumeratorDigit   Fraction numerator single digit to test.
     * @param a_DenominatorDigit Fraction denominator single digit to test.
     * @param a_rvfractions      Fraction list.
     */
    void Problem33::FindEqualFractions(uint32_t a_Numerator, 
                                       uint32_t a_Denominator, 
                                       uint32_t a_NumeratorDigit, 
                                       uint32_t a_DenominatorDigit, 
                                       FractionList& a_rvfractions)
    {
         // Either zero or division by zero
        if (a_NumeratorDigit == 0 || a_DenominatorDigit == 0)
        {
            return;
        }

        // We basically do a/b = c/d
        //           (b*d)*a/b = (b*d)*c/d
        //                 a*d = c*b
        // And we check that a*d does equal c*b
        uint32_t lhs = a_Numerator * a_DenominatorDigit;
        uint32_t rhs = a_NumeratorDigit * a_Denominator;

        // When both numerator are equals, we found a non trivial fraction
        if (lhs == rhs)
        {
            Fraction fraction(a_NumeratorDigit, a_DenominatorDigit);

            a_rvfractions.push_back(fraction);
        }
    }
}
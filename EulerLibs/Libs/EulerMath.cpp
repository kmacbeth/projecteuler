#include "EulerMath.h"

namespace EulerLib {

    /**
     * Test primality of a number
     *
     * Simple trial by division to decide if number is a prime.
     *
     * @param a_Number Number to test.
     *
     * @return Whether a_Number is prime or not.
     */
    bool PrimalityTest(uint32_t a_Number)
    {
        for (uint32_t i = 2; i < a_Number; ++i)
        {
            if (a_Number % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    /**
     * Greatest Common Divisor.
     *
     * This is the binary BCD algorithm.
     * Reference: https://en.wikipedia.org/wiki/Binary_GCD_algorithm
     *
     * @param a_Lhs Left-hand side number.
     * @param a_Rhs Right-hand side number.
     *
     * @return Greatest common divisor of Lhs and Rhs.
     */
    uint32_t GCD(uint32_t a_Lhs, uint32_t a_Rhs)
    {
        uint32_t shift = 0;

        if (a_Lhs == 0) return a_Rhs;
        if (a_Rhs == 0) return a_Lhs;

        // While a and b are even, increment shift
        while (((a_Lhs | a_Rhs) & 0x1) == 0)
        {
            a_Lhs >>= 1;
            a_Rhs >>= 1;
            shift++;
        }

        // Make sure a is alway odd for next step
        while ((a_Lhs & 0x1) == 0)
        {
            a_Lhs >>= 1;
        }

        do {
            // While b i even, reduce to odd
            while ((a_Rhs & 0x1) == 0)
            {
                a_Rhs >>= 1;
            }

            // Both a,b are odd
            if (a_Lhs > a_Rhs)
            {
                std::swap(a_Lhs, a_Rhs);
            }
            a_Rhs -= a_Lhs;

        } while (a_Rhs != 0);


        return a_Lhs << shift;
    }


    /**
     * Reverse integer digits in base 10.
     *
     * @param a_Number Number to reverse.
     *
     * @return Reversed number
     */
    uint64_t Reverse(uint64_t a_Number)
    {
        uint64_t result = 0;

        while (a_Number > 0)
        {
            result *= 10;
            result += (a_Number % 10);
            a_Number /= 10;
        }

        return result;
    }

    /**
     * Is number palindromic (any base)
     *
     * @param a_Number Number to test.
     * @param a_Base   Base for test.
     *
     * @return Whether the number is palindromic or not.
     */
    bool IsPalindromic(uint64_t a_Number, uint32_t a_Base)
    {
        uint64_t reverseNumber = 0;
        uint64_t result = a_Number;

        // Reverse base 10 digit then if the number is still the same
        // we got a palindrom number
        while(result > 0)
        {
            reverseNumber = (reverseNumber * a_Base) + (result % a_Base);
            result /= a_Base;
        }

        return (a_Number == reverseNumber);
    }

    /**
     * Number is pandigital test.
     *
     * @param a_Number       Number to test.
     * @param a_NumDigits    Number of digits to use
     * @param a_bIncludeZero Include digit '0' in equation.
     *
     * @return Whether the number is pandigital or not.
     */
    bool IsPandigital(uint32_t a_Number, uint32_t a_NumDigits, bool a_bIncludeZero)
    {
        uint8_t digits[10] = { 0 };
        uint32_t n = a_Number;

        for (uint32_t i = 0; i < a_NumDigits; ++i)
        {
            if (!a_bIncludeZero && n % 10 == 0)
            {
                return false;
            }

            digits[n % 10]++;
            
            if (digits[n % 10] > 1)
            {
                return false;
            }

            n /= 10;
        }

        uint32_t sum = 0;
        uint32_t start = (a_bIncludeZero ? 0 : 1);
        uint32_t end = a_NumDigits + start;

        for(uint32_t i = start; i < end; ++i)
        {
            sum += digits[i];
        }

        return (sum == a_NumDigits);
    }
    
}
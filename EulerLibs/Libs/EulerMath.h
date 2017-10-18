#ifndef __EULER_MATH_H__
#define __EULER_MATH_H__

#include "Euler.h"

namespace EulerLib {

    /**
     * Square root of a number.
     *
     * This is basically a square root for integer numbers.
     *
     * @param value A number representation.
     *
     * @return Square root of the value.
     */
    template<typename T> T SquareRoot(T a_Value)
    {
        double fltValue      = static_cast<double>(a_Value);
        double fltSquareRoot = std::ceil(std::sqrt(fltValue));

        return static_cast<T>(fltSquareRoot);
    }

    /**
     * Square root of a double (template specialization)
     *
     * @param a_fltValue Floating point number.
     *
     * @return Square root of the value.
     */
    template<> inline double SquareRoot(double a_fltValue)
    {
        return std::sqrt(a_fltValue);
    }

    /**
     * Round to nearest even.
     *
     * @param a_fltNumber Number to round
     *
     * @return Rounded number.
     */
    inline double Round(double a_fltNumber)
    {
        // Round to nearest even
        double fltFloorNumber = std::floor(a_fltNumber);
        double diff = a_fltNumber - fltFloorNumber;

        bool bIsEven = ((static_cast<uint64_t>(fltFloorNumber) & 0x1) == 0);

        if (diff < 0.5 || (diff == 0.5 && bIsEven))
        {
            return fltFloorNumber;
        }
        else
        {
            return std::ceil(a_fltNumber);
        }
    }

    /**
     * Modulus operator
     *
     * It applies the real operation on negative number, e.g.:
     *
     * -1 mod 4 = 3 not -1
     *
     * @param a_Number  Number
     * @param a_Divider Divider number.
     *
     * @return Modulus result.
     */
    template<typename T> inline T Modulus(T a_Number, T a_Divider)
    {
        if (a_Divider == 0) return 0;

        if (a_Number > 0)
        {
            return a_Number % a_Divider;
        }
        else
        {
            return (a_Divider + a_Number % a_Divider) % a_Divider;
        }
    }

    /**
     * Compute factorial of a number
     *
     * @param a_Number Number to compute factorial from.
     *
     * @return Factorial result.
     */
    template<typename T> inline T Factorial(T a_Number)
    {
        // 0! = 1
        T result = a_Number > 0 ? a_Number : 1;
        
        // 0! and 1!
        if (result < 2)
        {
            return result;
        }

        a_Number -= 1;

        if (result > 0)
        {
            while (a_Number > 0)
            {
                result *= a_Number;
                a_Number -= 1;
            }
        }

        return result;
    }

    /**
     * Exponentiation
     *
     * Using exponentiation by square to lighten computations.
     * Reference: https://en.wikipedia.org/wiki/Exponentiation_by_squaring#Basic_method
     *
     * @param a_Base     Base
     * @param a_Exponent Exponent
     *
     * @return Returns the power Base**Exponent.
     */
    template<typename T> T Power(T a_Base, uint64_t a_Exponent)
    {
        T result = 1;

        if (a_Exponent == 0) return result;

        // Iterative exponentiation by squaring
        while (a_Exponent > 1)
        {
            if ((a_Exponent & 0x1) == 1) // Odd
            {
                result *= a_Base;
                a_Exponent--;
            }

            a_Exponent >>= 1;
            a_Base *= a_Base;
        }

        result *= a_Base;

        return result;
    }
    
    /**
     * Test primality of a number
     */
    bool PrimalityTest(uint32_t number);

    /**
     * Right-shift digit in base 10.
     *
     * @param a_Number Number to right shift
     * @param a_Shift  Number of time to shift
     *
     * @return Result of right shifting.
     */
    template<typename T> inline T RightShift(T a_Number, uint32_t a_Shift)
    {
        while (a_Shift > 0)
        {
            a_Number /= 10;
            a_Shift--;
        }

        return a_Number;
    }

    /**
     * Left-shift digit in base 10.
     *
     * @param a_Number Number to left shift.
     * @param a_Shift  Number of time to shift
     *
     * @return Result of left shifting.
     */
    template<typename T> inline T LeftShift(T a_Number, uint32_t a_Shift)
    {

        while (a_Shift > 0)
        {
            a_Number *= 10;
            a_Shift--;
        }

        return a_Number;
    }

    /**
     * Rotate digits (right rotation)
     *
     * @param a_Number      Number to rotate.
     * @param a_NumRotation Number of rotation to perform.
     * @param a_DigitCount  Number of digit in the number.
     *
     * @return Returns the rotated number.
     */
    template<class T>
    inline T Rotate(T a_Number, uint32_t a_NumRotation, uint32_t a_DigitCount)
    {
        const T kBase = 10;
        T number = a_Number;

        // Beware, we must do a % numDigit to rotations...
        uint32_t numRotation = a_NumRotation % a_DigitCount;
        uint32_t divider = Power(kBase, numRotation);
        uint32_t multiplier = Power(kBase, a_DigitCount - numRotation);

        // Right rotate most significant digits, so they need to move to
        // the least significant digits place
        a_Number /= divider;

        // Right rotate least significant digits, so they need to move back
        // to the most significant digits place
        number %= divider;
        number *= multiplier;

        return (number + a_Number);
    }

    /**
     * Greatest Common Divisor
     */
    uint32_t GCD(uint32_t a_Lhs, uint32_t a_Rhs);


    /**
     * Least Common Multiple.
     *
     * @param a_Lhs Left-hand side number
     * @param a_Rhs Right-hand side number
     *
     * @return Least common multiple between Lhs and Rhs.
     */
    inline uint32_t LCM(uint32_t a_Lhs, uint32_t a_Rhs)
    {
        if ((a_Lhs | a_Rhs) == 0)
        {
            return 0;
        }

        return (a_Lhs / GCD(a_Lhs, a_Rhs)) * a_Rhs;
    }

    /**
     * Reverse integer
     */
    uint64_t Reverse(uint64_t a_Number);

    /**
     * Number is Palindromic in any base
     */
    bool IsPalindromic(uint64_t a_Number, uint32_t a_Base);

    /**
     * Number is Pandigital
     */
    bool IsPandigital(uint32_t a_Number, uint32_t a_NumDigits, bool a_bIncludeZero = false);

    /**
     * Count digits in base 10.
     *
     * @param a_Number Number.
     *
     * @return Number of digits.
     */
    template<typename T> uint32_t CountDigits(T a_Number)
    {
        T n = a_Number;
        uint32_t d = 0;

        // When zero
        if (!a_Number)
        {
            return 1;
        }

        while (n > 0)
        {
            n /= 10;
            d++;
        }

        return d;
    }

    /**
     * Triangle number test.
     *
     * @param a_Number Number to test.
     *
     * @return Whether a_Number is a triangle number or not.
     */
    inline bool IsTriangularNumber(uint64_t a_Number)
    {
        double n = (SquareRoot(8.0 * static_cast<double>(a_Number) + 1.0) - 1.0) / 2.0;

        return (n == Round(n));
    }

	/**
	 * Pentagonal number test.
	 *
	 * @param a_Number Number to test.
	 *
	 * @return Whether a_Number is a pentagonal number or not.
	 */
	inline bool IsPentagonalNumber(uint64_t a_Number)
	{
		double n = (SquareRoot(24.0 * static_cast<double>(a_Number) + 1.0) + 1.0) / 6.0;

		return (n == Round(n));
	}

	/**
	* Hexagonal number test.
	*
	* @param a_Number Number to test.
	*
	* @return Whether a_Number is a hexagonal number or not.
	*/
	inline bool IsHexagonalNumber(uint64_t a_Number)
	{
		double n = (SquareRoot(8.0 * static_cast<double>(a_Number) + 1.0) + 1.0) / 4.0;

		return (n == Round(n));
	}

    /**
     * Generate binomial coefficient.
     *
     * Also useful for k-Combinations.
     *
     * @param a_N The total number of coefficents
     * @param a_K Which coefficient number. (Starting at zero up to N)
     *
     * @return Coeffient.
     */
    template<typename T> T GetBinomialCoefficient(T a_N, T a_K)
    {
        if (a_K > a_N)
        {
            return 0;
        }

        T res = 1;
        for (T d = 1; d <= a_K; ++d)
        {
            res *= a_N--;
            res /= d;
        }

        return res;
    }
}

#endif // __EULER_MATH_H__
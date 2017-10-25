#include "TestEulerMath.h"
#include "Libs/EulerMath.h"

namespace EulerTest {

    using namespace EulerLib;

    /**
     * Run tests.
     */
    bool TestEulerMath::Run()
    {
        TestSquareRoot();
        TestRound();
        TestModulo();
        TestFactorial();
        TestRotate();
        TestGCD();
        TestPalindromicNumber();
        TestPandigitalNumber();
        TestCountDigits();
        TestPower();
        TestBase10Shifts();
        TestIsTriangularNumber();
        TestIsPentagonalNumber();
        TestIsHexagonalNumber();
        TestFindCombinations();

        return true;
    }

    /**
     * Test interal square root function
     */
    void TestEulerMath::TestSquareRoot()
    {
        std::cout << __FUNCTION__;

        // Square root uint32_t perfect square
        uint32_t value1 = 256;
        uint32_t sqrt1 = SquareRoot(value1);
        assert(sqrt1 == 16);

        // Square root uint32_t not perfect square
        uint32_t value2 = 1000;
        uint32_t sqrt2 = SquareRoot(value2);
        assert(sqrt2 == 32);

        // Square root double not perfect square
        double value3 = 1000.0;
        double sqrt3 = SquareRoot(value3);
        assert(sqrt3 != 32.0);
        assert(sqrt3 != 31.0);

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test rounding to nearest even function
     */
    void TestEulerMath::TestRound()
    {
        std::cout << __FUNCTION__;

        // Round 5.25
        assert(Round(5.25) == 5.0);

        // Round 5.75
        assert(Round(5.75) == 6.0);

        // Round 5.5
        assert(Round(5.5) == 6.0);

        // Round 4.5
        assert(Round(4.5) == 4.0);

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test real modulo.
     */
    void TestEulerMath::TestModulo()
    {
        std::cout << __FUNCTION__;

        // Test positive number < modulus
        assert(Modulus(3, 5) == 3);

        // Test positive number = modulus
        assert(Modulus(3, 3) == 0);

        // Test positive number > modulus
        assert(Modulus(4, 3) == 1);

        // Test negative number < modulus
        assert(Modulus(-3, 5) == 2);

        // Test positive number = modulus
        assert(Modulus(-3, 3) == 0);

        // Test positive number > modulus
        assert(Modulus(-4, 3) == 2);

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test factorial.
     */
    void TestEulerMath::TestFactorial()
    {
        std::cout << __FUNCTION__;

        // Test 0!
        assert(Factorial(0ul) == 1);

        // Test 1!
        assert(Factorial(1ul) == 1);

        // Test 2!
        assert(Factorial(2ul) == 2);

        // Test 5!
        assert(Factorial(5ul) == 120);

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test rotate digits
     */
    void TestEulerMath::TestRotate()
    {
        std::cout << __FUNCTION__;

        // Test case that include force modulo to go back to zero
        assert(Rotate(1234ul, 0, 4) == 1234 && "Not such rotation");
        assert(Rotate(1234ul, 1, 4) == 4123 && "Not such rotation");
        assert(Rotate(1234ul, 2, 4) == 3412 && "Not such rotation");
        assert(Rotate(1234ul, 3, 4) == 2341 && "Not such rotation");
        assert(Rotate(1234ul, 4, 4) == 1234 && "Not such rotation");
        assert(Rotate(1234ul, 5, 4) == 4123 && "Not such rotation");
        assert(Rotate(1234ul, 6, 4) == 3412 && "Not such rotation");
        assert(Rotate(1234ul, 7, 4) == 2341 && "Not such rotation");
        assert(Rotate(1234ul, 8, 4) == 1234 && "Not such rotation");

        // Test case with digit = 0 rolling number back into
        const uint32_t kDigitCount = 4;
        uint32_t number = 1034;

        for (uint32_t i = 0; i < kDigitCount; ++i)
        {
            number = Rotate(number, 1, kDigitCount);
        }

        assert(number == 1034 && "Not such rotation");

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test greatest common divisor.
     */
    void TestEulerMath::TestGCD()
    {
        std::cout << __FUNCTION__;

        // Simple GCD
        assert(GCD(6, 8) == 2);
        assert(GCD(8, 24) == 8);

        // GCD of two primes
        assert(GCD(5, 7) == 1);

        // GCD with one or two zero
        assert(GCD(4, 0) == 4);
        assert(GCD(0, 0) == 0);

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test palindromic number
     */
    void TestEulerMath::TestPalindromicNumber()
    {
        std::cout << __FUNCTION__;

        // Test base 10 small palindrom
        assert(IsPalindromic(585, 10));

        // Test base 2 small palindrom
        assert(IsPalindromic(585, 2));

        // Test not palindromic
        assert(!IsPalindromic(100, 10));

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test pandigital number
     */
    void TestEulerMath::TestPandigitalNumber()
    {
        std::cout << __FUNCTION__;

        // Test 5-digit pandigital number
        assert(IsPandigital(12345, 5));

        // Test 9-digit pandigital number
        assert(IsPandigital(976431852, 9));

        // Test non-pandigital number (no duplicate digit, but one zero)
        assert(!IsPandigital(38701, 5));

        // Test non-pandigital number (duplicate digit, but no zero)
        assert(!IsPandigital(123345, 6));

        // Test non-pandigital number that show up a bug
        assert(!IsPandigital(7654319, 7));

        // Test pandigital number including digit 0
        assert(IsPandigital(1230, 4, true));

        // Test pandigital number including digit 0 at MSB
        assert(IsPandigital( 123, 4, true));

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test count digits.
     */
    void TestEulerMath::TestCountDigits()
    {
        std::cout << __FUNCTION__;

        // Count 5 digits
        assert(CountDigits(12345) == 5);

        // Count 5-digit but insert zero
        assert(CountDigits(0) == 1);

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test power function template.
     */
    void TestEulerMath::TestPower()
    {
        std::cout << __FUNCTION__;

        // Just test basic property
        assert(Power<uint16_t>(3,  0) ==  1);
        assert(Power<uint16_t>(3,  1) ==  3);

        // Power of uint32_t
        assert(Power<uint32_t>(2, 31) == 0x80000000);
        assert(Power<uint32_t>(3,  3) == 27);

        // Power of uint64_t
        assert(Power<uint64_t>(2, 32) == 0x100000000);

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test left and right shifts in base 10
     */
    void TestEulerMath::TestBase10Shifts()
    {
        std::cout << __FUNCTION__;

        // Right shift digits - 1
        assert(RightShift(234, 2) == 2);

        // Right shift digits
        assert(RightShift(234, 3) == 0);

        // Right shift digits + 1
        assert(RightShift(234, 4) == 0);

        // Right shift 0 digit
        assert(RightShift(234, 0) == 234);

        // Left shift one digit
        assert(LeftShift(234, 1) == 2340);

        // Left shift zero digit
        assert(RightShift(234, 0) == 234);

        // Right shift 10 digits (out of 32-bit integer)
        assert(RightShift(234, 10) == 0);

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test IsTriangularNumber
     */
    void TestEulerMath::TestIsTriangularNumber()
    {
        std::cout << __FUNCTION__;

        uint32_t triangular[5] = { 0, 1, 3, 10, 300 };
        uint32_t nonTriangular[5] = { 2, 5, 14, 275, 405 };

        // Test triangular numbers
        for (uint32_t n = 0; n < 5; ++n)
        {
            assert(IsTriangularNumber(triangular[n]));
        }

        // Test non triangular numbers
        for (uint32_t n = 0; n < 5; ++n)
        {
            assert(!IsTriangularNumber(nonTriangular[n]));
        }

        std::cout << "... PASS" << std::endl;
    }

    /**
    * Test IsPentagonalNumber
    */
    void TestEulerMath::TestIsPentagonalNumber()
    {
        std::cout << __FUNCTION__;

        uint32_t pentagonal[5] = { 1, 5, 12, 22, 35 };
        uint32_t nonPentagonal[5] = { 2, 7, 14, 30, 100 };

        // Test pentagonal numbers
        for (uint32_t n = 0; n < 5; ++n)
        {
            assert(IsPentagonalNumber(pentagonal[n]));
        }

        // Test non pentagonal numbers
        for (uint32_t n = 0; n < 5; ++n)
        {
            assert(!IsPentagonalNumber(nonPentagonal[n]));
        }

        std::cout << "... PASS" << std::endl;
    }

    /**
    * Test IsHexagonalNumber
    */
    void TestEulerMath::TestIsHexagonalNumber()
    {
        std::cout << __FUNCTION__;

        uint32_t hexagonal[5] = { 1, 6, 15, 28, 45 };
        uint32_t nonHexagonal[5] = { 3, 12, 18, 27, 46 };

        // Test hexagonal numbers
        for (uint32_t n = 0; n < 5; ++n)
        {
            assert(IsHexagonalNumber(hexagonal[n]));
        }

        // Test non hexagonal numbers
        for (uint32_t n = 0; n < 5; ++n)
        {
            assert(!IsHexagonalNumber(nonHexagonal[n]));
        }

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test k-combinations.
     */
    void TestEulerMath::TestFindCombinations()
    {
        std::cout << __FUNCTION__;

        // Find n = 5, k = 0..5
        assert(GetBinomialCoefficient(5, 0) == 1);
        assert(GetBinomialCoefficient(5, 1) == 5);
        assert(GetBinomialCoefficient(5, 2) == 10);
        assert(GetBinomialCoefficient(5, 3) == 10);
        assert(GetBinomialCoefficient(5, 4) == 5);
        assert(GetBinomialCoefficient(5, 5) == 1);

        // Find n = 23, k = 10
        assert(GetBinomialCoefficient(23, 10) == 1144066);

        // Find n = 10, k = 10
        assert(GetBinomialCoefficient(10, 10) == 1);

        // Find n = 10, k = 23
        assert(GetBinomialCoefficient(10, 23) == 0);

        std::cout << "... PASS" << std::endl;
    }
}
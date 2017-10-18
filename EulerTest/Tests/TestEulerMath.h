#ifndef __EULER_TEST_MATH_H__
#define __EULER_TEST_MATH_H__

#include "EulerTest.h"

namespace EulerTest {

    class TestEulerMath : public TestCase {

    public:
        TestEulerMath() : TestCase("EulerMath")
        {}

        bool Run();


    private:
        void TestSquareRoot();
        void TestRound();
        void TestModulo();
        void TestFactorial();
        void TestRotate();
        void TestGCD();
        void TestPalindromicNumber();
        void TestPandigitalNumber();
        void TestCountDigits();
        void TestPower();
        void TestBase10Shifts();
        void TestIsTriangularNumber();
		void TestIsPentagonalNumber();
		void TestIsHexagonalNumber();
        void TestFindCombinations();
    };

}

#endif // __EULER_TEST_MATH_H__
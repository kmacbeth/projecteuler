#ifndef __EULER_TEST_PRIMEFACTORIZER_H__
#define __EULER_TEST_PRIMEFACTORIZER_H__

#include "EulerTest.h"

namespace EulerTest {

    class TestPrimeFactorizer : public TestCase {

    public:
        TestPrimeFactorizer() : TestCase("PrimeFactorizer")
        {}

        bool Run();

    private:
        void TestFactorization();
        void TestPerformance();
    };

    class PerfPrimeFactorizer : public TestCase {

    public:
        PerfPrimeFactorizer() : TestCase("PrimeFactorizer.perf")
        {}

        bool Run();

    private:
        void TestPerformance();
    };
}


#endif // __EULER_TEST_PRIMEFACTORIZER_H__
#ifndef __EULER_TEST_PRIMECOUNTER_H__
#define __EULER_TEST_PRIMECOUNTER_H__

#include "EulerTest.h"

namespace EulerTest {

    class TestPrimeCounter : public TestCase {

    public:
        TestPrimeCounter() : TestCase("PrimeCounter")
        {}

        bool Run();

    private:
        void TestCountPrime();
    };

}


#endif // __EULER_TEST_PRIMECOUNTER_H__
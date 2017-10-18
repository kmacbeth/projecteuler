#ifndef __EULER_TEST_ERATOSTHENESSIEVE_H__
#define __EULER_TEST_ERATOSTHENESSIEVE_H__

#include "EulerTest.h"

namespace EulerTest {

    class TestEratosthenesSieve: public TestCase {

    public:
        TestEratosthenesSieve() : TestCase("EratosthenesSieve")
        {}

        bool Run();

    private:
        static const uint32_t kPrimePool[];

        void TestComputeEratostheneSieve();
        void TestComputeSegmentedSieve();
        void TestSievingSqrtEqualDelta();
    };

}


#endif // __EULER_TEST_ERATOSTHENESSIEVE_H__
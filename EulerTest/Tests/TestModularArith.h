#ifndef __EULER_TEST_MODULARARITH_H__
#define __EULER_TEST_MODULARARITH_H__

#include "EulerTest.h"

namespace EulerTest {

    class TestModularArith : public TestCase {

    public:
        TestModularArith() : TestCase("ModularArith")
        {}

        bool Run();

    private:
        void TestAddition();
        void TestSubtraction();
        void TestMultiplication();
        void TestExponentiation();
    };

}

#endif // __EULER_TEST_MODULARARITH_H__
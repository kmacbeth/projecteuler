#ifndef __EULER_TEST_DIVISORFUNCTION_H__
#define __EULER_TEST_DIVISORFUNCTION_H__

#include "EulerTest.h"

namespace EulerTest {

    class TestDivisorFunction : public TestCase {

    public:
        TestDivisorFunction() : TestCase("DivisorFunction")
        {}

        bool Run();

    private:
        void TestFunction();
    };

}


#endif // __EULER_TEST_DIVISORFUNCTION_H__
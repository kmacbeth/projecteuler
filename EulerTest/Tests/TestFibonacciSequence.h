#ifndef __EULER_TEST_FIBONACCISEQUENCE_H__
#define __EULER_TEST_FIBONACCISEQUENCE_H__

#include "EulerTest.h"

namespace EulerTest {

    class TestFibonacciSequence : public TestCase {

    public:
        TestFibonacciSequence() : TestCase("FibonacciSequence") {}
        ~TestFibonacciSequence() {}
            
        bool Run();

    private:
        // Instanciation and represention tests.
        void TestFunctorQword();
        void TestFunctorBigInteger();

    };

}

#endif // __EULER_TEST_FIBONACCISEQUENCE_H__
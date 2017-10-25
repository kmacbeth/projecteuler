#ifndef __EULER_TEST_BIGINTEGER_H__
#define __EULER_TEST_BIGINTEGER_H__

#include "EulerTest.h"

namespace EulerTest {

    class TestBigInteger : public TestCase {

    public:
        TestBigInteger() : TestCase("BigInteger") {}
        ~TestBigInteger() {}

        bool Run();

    private:
        // Instanciation and represention tests.
        void TestConstructors();
        void TestOperatorAssign();
        void TestToString();

        // Boolean comparison tests.
        void TestOperatorSmallerThan();
        void TestOperatorGreaterThan();
        void TestOperatorSmallerThanOrEquals();
        void TestOperatorGreaterThanOrEquals();
        void TestOperatorEquals();
        void TestOperatorNotEquals();

        // Arithmetic tests.
        void TestAddBins();
        void TestOperatorAddAssign();
        void TestOperatorMulAssign();
    };

}


#endif // __EULER_TEST_BIGINTEGER_H__
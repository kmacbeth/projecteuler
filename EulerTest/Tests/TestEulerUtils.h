#ifndef __EULER_TEST_UTILS_H__
#define __EULER_TEST_UTILS_H__

#include "EulerTest.h"

namespace EulerTest {

    class TestEulerUtils : public TestCase {

    public:
        TestEulerUtils() : TestCase("EulerUtils")
        {}

        bool Run();

    private:
        void TestReadFile();
        void TestTokenize();
        void TestToNumber();
		void TestToVector();
    };

}

#endif // __EULER_TEST_UTILS_H__
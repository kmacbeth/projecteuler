#ifndef __EULER_TEST_LEXICOGRAPHICPERMUTATION_H__
#define __EULER_TEST_LEXICOGRAPHICPERMUTATION_H__

#include "EulerTest.h"

namespace EulerTest {

    class TestLexicographicPermutation : public TestCase {

    public:
        TestLexicographicPermutation() : TestCase("LexicographicPermutation")
        {}

        bool Run();

    private:
        void TestPermutations();
    };

}

#endif // __EULER_TEST_LEXICOGRAPHICPERMUTATION_H__
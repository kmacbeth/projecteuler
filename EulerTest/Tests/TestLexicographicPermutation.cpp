#include "TestLexicographicPermutation.h"
#include "Libs/LexicographicPermutation.h"

namespace EulerTest {

    using namespace EulerLib;

    /**
     * Run tests.
     */
    bool TestLexicographicPermutation::Run()
    {
        TestPermutations();

        return true;
    }


    /**
     * Test some permutations
     */
    void TestLexicographicPermutation::TestPermutations()
    {
        std::cout << __FUNCTION__;

        uint32_t testVector[] = { 1, 2, 3, 4, 5 };
        
        LexicographicPermutator permute;
        std::vector<uint32_t> vPermutation(testVector, testVector + 5);
        
        // We have 120 possibilities, start with fifth
        for (uint32_t i = 0; i < 5; ++i)
        {
            permute(vPermutation);
        }
        assert(vPermutation[0] == 1);
        assert(vPermutation[1] == 2);
        assert(vPermutation[2] == 5);
        assert(vPermutation[3] == 3);
        assert(vPermutation[4] == 4);

        // Find tenth
        for (uint32_t i = 0; i < 5; ++i)
        {
            permute(vPermutation);
        }
        assert(vPermutation[0] == 1);
        assert(vPermutation[1] == 3);
        assert(vPermutation[2] == 4);
        assert(vPermutation[3] == 5);
        assert(vPermutation[4] == 2);

        // Find last permutation
        for (uint32_t i = 0; i < 110; i++)
        {
            permute(vPermutation);
        }
        assert(vPermutation[0] == 5);
        assert(vPermutation[1] == 4);
        assert(vPermutation[2] == 3);
        assert(vPermutation[3] == 2);
        assert(vPermutation[4] == 1);

        // Permute until return false
        bool bContinue = true;
        uint32_t timeout = 0;

        while (bContinue)
        {
            bContinue = permute(vPermutation);

            // Timeout, otherwise it may run forever if it's buggy
            ++timeout;

            if (timeout == 0xFFFFFFFF)
            {
                break;
            }
        }

        assert(!bContinue && "Permutation never ended.");

        std::cout << "... PASS" << std::endl;
    }

}
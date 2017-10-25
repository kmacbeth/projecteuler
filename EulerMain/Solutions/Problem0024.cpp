#include "Problem0024.h"
#include "Libs\EulerUtils.h"
#include "Libs\LexicographicPermutation.h"

namespace Euler {

    /**
     * Problem: Lexicographic permutations
     *
     * A permutation is an ordered arrangement of objects. For example, 3124 is one
     * possible permutation of the digits 1, 2, 3 and 4. If all of the permutations
     * are listed numerically or alphabetically, we call it lexicographic order. The
     * lexicographic permutations of 0, 1 and 2 are:
     *
     *                    012   021   102   120   201   210
     *
     * What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4,
     * 5, 6, 7, 8 and 9.
     */
    void Problem24::Solve()
    {
        // Reference: https://www.nayuki.io/page/next-lexicographical-permutation-algorithm
        // There are 10! combinations (3628800) we need to find the 1000000th
        uint32_t numbers[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        const uint32_t kNumberSize = sizeof(numbers) / sizeof(numbers[0]);
        const uint32_t kLimit = 1000000;

        // Perform permutations
        EulerLib::LexicographicPermutator permute;
        std::vector<uint32_t> vPermutation(numbers, numbers + kNumberSize);

        for(uint32_t k = 0; k < kLimit; ++k)
        {
            permute(vPermutation);
        }

        uint64_t result = EulerLib::ToNumber<uint64_t>(vPermutation);

        SetAnswer(result);
    }

}

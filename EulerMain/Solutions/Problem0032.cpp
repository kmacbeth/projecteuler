#include "Problem0032.h"
#include "Libs\EulerUtils.h"
#include "Libs\LexicographicPermutation.h"

namespace Euler {

    /**
     * Problem: Pandigital products
     *
     * We shall say that an n-digit number is pandigital if it makes use of all
     * the digits 1 to n exactly once; for example, the 5-digit number, 15234,
     * is 1 through 5 pandigital.
     *
     * The product 7254 is unusual, as the identity, 39 × 186 = 7254,
     * containing multiplicand, multiplier, and product is 1 through 9
     * pandigital.
     *
     * Find the sum of all products whose multiplicand/multiplier/product
     * identity can be written as a 1 through 9 pandigital.
     *
     * HINT: Some products can be obtained in more than one way so be sure to
     * only include it once in your sum.
     */
    void Problem32::Solve()
    {
        // This is sort of a brute-force approach.
        // We will start by generating all permutations using algorithm from
        // problem 24. Than, for each permutation, we need to check all
        // m x n = p possibilities. We need to remember that we have p-digits
        // is at most m-digits + n-digits.
        const uint32_t kNumbers[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        const uint32_t kNumberSize = sizeof(kNumbers) / sizeof(kNumbers[0]);
        // Maximum number of permutation for 9 elements is 9! = 362880
        const uint32_t kLimit = 362880;

        //We use a set since duplicates may happen that satisfy the equation
        std::set<uint32_t> sResults;

        EulerLib::LexicographicPermutator permute;
        std::vector<uint32_t> vPermutation(kNumbers, kNumbers + kNumberSize);

        for(uint32_t k = 0; k < kLimit; ++k)
        {
            if (permute(vPermutation))
            {
                // Dump permutation into integer max is 987654321
                uint32_t number = EulerLib::ToNumber<uint32_t>(vPermutation);
                uint32_t rhs = number % 10000; // Extract least significant digits

                // Check all possible multiplication where the number of digits
                // make sense. Basically we will have:
                //     1-4 digits x 4-1 digits = 4 digits.
                // Furthermore, the multiplier and multiplicand will be interchanged
                // in another permutation, thus creating a duplicate product, so we
                // can only test the first two cases. Example:
                //   Permutation   123456789  512346789
                //               -> 1 * 2345  5 * 1234
                //               -> 12 * 345  51 * 234
                //               -> 123 * 45  512 * 34
                //               -> 1234 * 5  5123 * 4
                // We have 1234 * 5 and 5 * 1234 that is a duplicated product in the
                // later one for the same last 4-digits.
                for (uint32_t c = 1; c < 100; c *= 10)
                {
                    uint32_t multiplicand  = number / (100000000 / c);     // Extract most significant digits
                    uint32_t multiplier = (number / 10000) % (10000 / c ); // Extract remaining center digits
                    uint32_t product = multiplicand * multiplier;

                    if (product == rhs)
                    {
                        sResults.insert(rhs);
                    }
                }
            }
        }

        // For each element of the set, compute the sum
        uint32_t result = 0;
        std::set<uint32_t>::const_iterator itResult = sResults.begin();

        for (; itResult != sResults.end(); ++itResult)
        {
            result += *itResult;
        }

        SetAnswer(result);
    }
}
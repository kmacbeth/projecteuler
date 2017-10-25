#include "Problem0043.h"
#include "Libs\EulerUtils.h"
#include "Libs\EulerMath.h"
#include "Libs\LexicographicPermutation.h"

namespace Euler {

    /**
     * Problem: Sub-string divisibility
     *
     * The number, 1406357289, is a 0 to 9 pandigital number because it is made
     * up of each of the digits 0 to 9 in some order, but it also has a rather
     * interesting sub-string divisibility property.
     *
     * Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way, we
     * note the following:
     *
     *  d2d3d4=406 is divisible by 2
     *  d3d4d5=063 is divisible by 3
     *  d4d5d6=635 is divisible by 5
     *  d5d6d7=357 is divisible by 7
     *  d6d7d8=572 is divisible by 11
     *  d7d8d9=728 is divisible by 13
     *  d8d9d10=289 is divisible by 17
     *
     *  Find the sum of all 0 to 9 pandigital numbers with this property.
     */
    void Problem43::Solve()
    {
        uint64_t result = 0;

        // We need to test all pandigital numbers with digits 0-9,
        // We can generate permutations from 0123456789 and check
        // for divisibility for these prime numbers.
        const uint32_t kInitPermutation[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        const uint32_t kNumDigits = sizeof(kInitPermutation) / sizeof(kInitPermutation[0]);

        EulerLib::LexicographicPermutator permute;
        std::vector<uint32_t> vPermutation(kInitPermutation, kInitPermutation + kNumDigits);

        const uint32_t kPrimes[] = { 2, 3, 5, 7, 11, 13, 17 };
        const uint32_t kPrimesSize = sizeof(kPrimes) / sizeof(kPrimes[0]);

        while (permute(vPermutation))
        {
            bool bIsDivisible = true;

            for (uint32_t i = 0; i < kPrimesSize && bIsDivisible; ++i)
            {
                // A 3-digit window to test primality
                uint32_t n = vPermutation[i + 1] * 100 + vPermutation[i + 2] * 10 + vPermutation[i + 3];

                if (n % kPrimes[i] != 0)
                {
                    bIsDivisible = false;
                }
            }

            if (bIsDivisible)
            {
                result += EulerLib::ToNumber<uint64_t>(vPermutation);
            }
        }

        SetAnswer(result);
    }
}
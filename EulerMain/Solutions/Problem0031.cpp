#include "Problem0031.h"

namespace Euler {

    /**
     * Problem: Coin sums
     *
     * In England the currency is made up of pound, £, and pence, p, and there
     * are eight coins in general circulation:
     *
     *     1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
     *
     * It is possible to make £2 in the following way:
     *
     *     1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
     *
     * How many different ways can £2 be made using any number of coins?
     */
    void Problem31::Solve()
    {
        const uint32_t kMaxCoins = 201; // 0p to 200p
        const uint32_t kCoins[] = { 1, 2, 5, 10, 20, 50, 100, 200 };
        const uint32_t kNumCoins = sizeof(kCoins) / sizeof(kCoins[0]);
        std::vector<uint32_t> combinations(kMaxCoins, 0);

        // Find the number of solution (cumulative solutions)
        // We will do an example with max coins 5p, but the same applies for Np
        //  +----+-------------------+
        //  | Xp | 0p 1p 2p 3p 4p 5p |
        //  +----+-------------------+
        //  | In | 1  0  0  0  0  0  | 0p has 1 combination (initial condition)
        //  | 1p | 1  1  1  1  1  1  |
        //  | 2p | 1  1  2  2  3  3  |
        //  | 5p | 1  1  2  2  3  4  |
        //  +----+-------------------+
        // How many combination of 1p to get 1p -> 1p - 1p = 0p, check 0p: 1 combination
        // How many combination of 1p to get 2p -> 2p - 1p = 1p, check 1p: 1 combination
        // How many combination of 1p to get 3p -> 3p - 1p = 2p, check 2p: 1 combination
        // How many combination of 1p to get 4p -> 4p - 1p = 3p, check 3p: 1 combination
        // How many combination of 1p to get 5p -> 5p - 1p = 4p, check 4p: 1 combination
        // -> Basically, there is only one combination with 1p to make Np >= 1p.
        // How many combination of 2p to get 2p -> 2p - 2p = 0p, check 0p: 1 combination,
        //     add to 2p, total 2 combinations
        // How many combination of 2p to get 3p -> 3p - 2p = 1p, check 1p: 1 combination,
        //     add to 3p, total 2 combinations
        // How many combination of 2p to get 4p -> 4p - 2p = 2p, check 2p: 2 combinations,
        //     add to 4p, total 3 combinations
        // How many combination of 2p to get 5p -> 5p - 2p = 3p, check 3p: 2 combinations,
        //     add to 5p, total 3 combinations
        // -> Basically, that's all the combination of 1p and/or 2p to make Np >= 2p.
        // How many combination of 5p to get 5p -> 5p - 5p = 0p, check 0p: 1 combination,
        //     add to 5p, total 4 combinations
        // -> Basically, that's all the combinations of 1p and/or 2p and/or 5p to make Np >= 5p
        combinations[0] = 1;

        for (uint32_t i = 0; i < kNumCoins; i++)
        {
            uint32_t curCoinValue = kCoins[i];

            for (uint32_t coinValue = curCoinValue; coinValue < kMaxCoins; ++coinValue)
            {
                combinations[coinValue] += combinations[coinValue - curCoinValue];
            }
        }

        uint32_t result = combinations[kMaxCoins-1];

        SetAnswer(result);
    }
}
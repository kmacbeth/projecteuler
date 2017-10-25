#include "Problem0015.h"
#include "Libs/EulerMath.h"

namespace Euler {

    /**
     * Problem: Lattice paths
     *
     * Starting in the top left corner of a 2×2 grid, and only being able to move
     * to the right and down, there are exactly 6 routes to the bottom right
     * corner.
     *
     *    ooooooo  oooo--+  oooo--+
     *    |  |  o  |  o  |  |  o  |
     *    +--+--o  +--oooo  +--o--+
     *    |  |  o  |  |  o  |  o  |
     *    +--+--v  +--+--v  +--ooo>
     *
     *    o--+--+  o--+--+  o--+--+
     *    o  |  |  o  |  |  o  |  |
     *    ooooooo  oooo--+  o--+--+
     *    |  |  o  |  o  |  o  |  |
     *    +--+--v  +--ooo>  oooooo>
     *
     * How many such routes are there through a 20×20 grid?
     */
    void Problem15::Solve()
    {
        // Reference: https://en.wikipedia.org/wiki/Lattice_path#Combinations_and_NE_lattice_paths
        //            https://en.wikipedia.org/wiki/Binomial_coefficient#Multiplicative_formula
        //
        // Number of lattice path from (0, 0) to (20, 20)
        //
        // Here,  (n) = ___n!___ is the binomial coefficient where n = n + k
        //        (k)   k!(n-k)!                               and k = n
        //
        const uint64_t kWidth = 20;
        const uint64_t kHeight = 20;

        uint64_t result = EulerLib::GetBinomialCoefficient(kWidth + kHeight, kHeight);

        SetAnswer(result);
    }

}

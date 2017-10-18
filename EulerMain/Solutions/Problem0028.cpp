#include "Problem0028.h"

namespace Euler {

    /**
     * Problem: Number spiral diagonals
     *
     * Starting with the number 1 and moving to the right in a clockwise
     * direction a 5 by 5 spiral is formed as follows:
     *
     *                        21 22 23 24 25
     *                        20  7  8  9 10
     *                        19  6  1  2 11
     *                        18  5  4  3 12
     *                        17 16 15 14 13
     *
     * It can be verified that the sum of the numbers on the diagonals is 101.
     *
     * What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral 
     * formed in the same way?
     */
    void Problem28::Solve()
    {
        // For each square NxN from 3x3, 5x5, ..., 1001x1001
        // Offset inside each square element is N-1
        // Since all square sides are odd, we iterate from 3,5,..,1001
        uint32_t kMinLimit = 1;
        uint32_t kMaxLimit = 1001;
        uint32_t kNumSide = 4;
        uint64_t cornerNumber = kMinLimit;
        uint64_t result = 1; // Center number (1)

        for (uint32_t sideLength = kMinLimit + 2; sideLength <= kMaxLimit; sideLength += 2)
        {
            // We starting a new square, the offset is adjust for the new square size
            for (uint32_t side = 0; side < kNumSide; ++side)
            {
                // We add an offset from the previous corner number and
                // we apply the same offset four times to add the number
                // from the four corner of the current square.
                // for each the
                cornerNumber += (sideLength - 1);

                // Total sum of numbers on the diagonal (corner numbers)
                result += cornerNumber;
            }
        }

        SetAnswer(result);
    }
    
}

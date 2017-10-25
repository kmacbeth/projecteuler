#include "Problem0018.h"
#include "Libs/EulerMath.h"

namespace Euler {

    /**
     * Problem: Maximum path sum 1
     *
     * By starting at the top of the triangle below and moving to adjacent numbers
     * on the row below, the maximum total from top to bottom is 23.
     *
     *                               3
     *                              7 4
     *                             2 4 6
     *                            8 5 9 3
     *
     * That is, 3 + 7 + 4 + 9 = 23.
     *
     * Find the maximum total from top to bottom of the triangle below:
     *
     *                                75
     *                              95 64
     *                             17 47 82
     *                           18 35 87 10
     *                          20 04 82 47 65
     *                        19 01 23 75 03 34
     *                       88 02 77 73 07 63 67
     *                     99 65 04 28 06 16 70 92
     *                    41 41 26 56 83 40 80 70 33
     *                  41 48 72 33 47 32 37 16 94 29
     *                 53 71 44 65 25 43 91 52 97 51 14
     *               70 11 33 28 77 73 17 78 39 68 17 57
     *              91 71 52 38 17 14 91 43 58 50 27 29 48
     *            63 66 04 68 89 53 67 30 73 16 69 87 40 31
     *           04 62 98 27 23 09 70 98 73 93 38 53 60 04 23
     *
     * NOTE: As there are only 16384 routes, it is possible to solve this problem
     * by trying every route. However, Problem 67, is the same challenge with a
     * triangle containing one-hundred rows; it cannot be solved by brute force,
     * and requires a clever method! ;o)
     */
    void Problem18::Solve()
    {
        // Use bottom-up approach:
        //        3
        //       7 4
        //      2 4 6
        //     8 5 9 3
        //
        // Start by check {2,4,6}
        //   For 2 max(8,5) = 8 -> 2+8 = 10
        //   For 4 max(5,9) = 9 -> 4+9 = 13
        //   For 6 max(9,3) = 0 -> 6+9 = 15
        //
        // Then, check {7,4} for the new nodes value
        //   For 7 max(10,13) = 13 -> 7 + 13 = 20
        //   For 4 max(13,15) = 15 -> 4 + 15 = 19
        //
        // Then check for {3} with new nodes value
        //   For 3 max(20,19) = 20 -> 3 + 20 = 23
        const uint32_t kNumRow = 15;
        uint64_t triangleTree[] = {
            75, 95, 64, 17, 47, 82, 18, 35, 87, 10, 20, 04, 82, 47, 65,
            19, 01, 23, 75, 03, 34, 88, 02, 77, 73, 07, 63, 67, 99, 65,
            04, 28, 06, 16, 70, 92, 41, 41, 26, 56, 83, 40, 80, 70, 33,
            41, 48, 72, 33, 47, 32, 37, 16, 94, 29, 53, 71, 44, 65, 25,
            43, 91, 52, 97, 51, 14, 70, 11, 33, 28, 77, 73, 17, 78, 39,
            68, 17, 57, 91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29,
            48, 63, 66, 04, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31,
            04, 62, 98, 27, 23,  9, 70, 98, 73, 93, 38, 53, 60, 04, 23
        };

        // Iterate each row, starting at the before last row
        for (uint32_t i = 1; i < kNumRow; ++i)
        {
            uint32_t index = kNumRow - 1 - i;
            uint32_t curRowSize = index + 1;
            uint32_t curRowIndex = 0;
            uint32_t nextRowIndex = EulerLib::GetBinomialCoefficient(index + 2, index);

            if (index != 0)
            {
                curRowIndex = EulerLib::GetBinomialCoefficient(index + 1, index - 1);
            }

            // Iterate each element of the row and add the greatest value between
            // the two adjacent nodes from the row below.
            for (uint32_t r = 0; r < curRowSize; ++r)
            {
                triangleTree[curRowIndex + r] += std::max(triangleTree[nextRowIndex + r],
                                                          triangleTree[nextRowIndex + r + 1]);
            }

        }

        uint64_t result = triangleTree[0];

        SetAnswer(result);
    }

}

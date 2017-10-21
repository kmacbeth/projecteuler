#include "Problem0052.h"
#include "Libs\EulerMath.h"

namespace Euler {

    /**
     * Problem: Permuted multipliertiples
     *
     * It can be seen that the number, 125874, and its double, 251748, contain
     * exactly the same digits, but in a different order.
     *
     * Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, 
     * contain the same digits.
     */
    void Problem52::Solve()
    {
		const uint32_t kLimit = 1000000000;
        uint32_t result = 0;
        
        uint32_t lowerBound = 1;
        uint32_t upperBound = 1;
 
        // We must have x # of digits = 6x # of digits,
        // So we need to test on a range of values of each n-digit numbers.
        // E.g.: [10000,16666]
		bool bSolutionFound = false;

        while (lowerBound < kLimit && !bSolutionFound)
        {
			// Adjust x by range [s, t] = [x0...0, x6...6]
			lowerBound *= 10;
			upperBound *= 10;
			upperBound += 6;

			for (uint32_t x = lowerBound; x <= upperBound && !bSolutionFound; ++x)
			{
				bSolutionFound = HasDigitsOccurenceEqual(x);
				if (bSolutionFound)
				{
					result = x;
				}
			}
        }

        SetAnswer(result);
    }

    /**
     * Verify digits occurence is equal between two numbers
     *
     * @param a Reference number
     * @param b Tested number
     *
     * @return Whether both number are equal or not.
     */
    bool Problem52::HasDigitsOccurenceEqual(uint32_t a_X)
    {
		const uint32_t kLowerMultiplier = 2;
		const uint32_t kHighestMultiplier = 6;
 		std::vector<uint32_t> vDigitsX(10, 0);
		std::vector<uint32_t> vDigitsProductX(10, 0);

		// Count each digit
		uint32_t x = a_X;

		while (x > 0)
		{
			++vDigitsX[x % 10];
			x /= 10;
		}

		// Try each multplier from 2x to 6x, the must all contains the same digits
		// but in different order.
		uint32_t multiplier = 0;

		for (multiplier = kLowerMultiplier; multiplier <= kHighestMultiplier; ++multiplier)
		{
			uint64_t productX = multiplier * a_X;

			// Insert digits of X into an HashSet (uniquify digits)
			while (productX > 0)
			{
				++vDigitsProductX[productX % 10];
					productX /= 10;
			}

			if (vDigitsX != vDigitsProductX)
			{
				return false;
			}

			std::fill(vDigitsProductX.begin(), vDigitsProductX.end(), 0);
		}

		return true;
    }
}

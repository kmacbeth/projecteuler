#include "Problem0038.h"
#include "Libs\EulerMath.h"

namespace Euler {

    /**
     * Problem: Pandigital multiples
     *
     * Take the number 192 and multiply it by each of 1, 2, and 3:
     *
     *  192 × 1 = 192
     *  192 × 2 = 384
     *  192 × 3 = 576
     *
     * By concatenating each product we get the 1 to 9 pandigital, 192384576.
     * We will call 192384576 the concatenated product of 192 and (1,2,3)
     *
     * The same can be achieved by starting with 9 and multiplying by 1, 2, 3,
     * 4, and 5, giving the pandigital, 918273645, which is the concatenated 
     * product of 9 and (1,2,3,4,5).
     *
     * What is the largest 1 to 9 pandigital 9-digit number that can be formed
     * as the concatenated product of an integer with (1,2, ... , n) where n > 1?
     */
    void Problem38::Solve()
    {
		const uint32_t kLimit = 9999;
		const uint32_t kMaxDigits = 9;
        uint32_t result = 0;

        for (uint32_t i = 1; i < kLimit; ++i)
        {
			uint32_t number = 0;
			uint32_t totalDigits = 0;

			for (uint32_t n = 1; n <= kMaxDigits; ++n)
			{
				// We will precompute the total number of digits to decide
				// when we can eliminate number earlier.
				uint32_t term = n * i;
				uint32_t digits = EulerLib::CountDigits(term);

				totalDigits += digits;

				// We only consider 9-digit numbers
				if (totalDigits <= kMaxDigits)
				{
					// Concatenate
					number = EulerLib::LeftShift(number, digits) + term;
				}
				if (totalDigits == kMaxDigits)
				{
					if (EulerLib::IsPandigital(number, kMaxDigits) && result < number)
					{
						result = number;
					}
				}
			}
        }

        SetAnswer(result);
    }
}
#include "Problem0017.h"

namespace Euler {

    /**
     * Problem: Number letter counts
     *
     * If the numbers 1 to 5 are written out in words: one, two, three, four, five,
     * then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
     *
     * If all the numbers from 1 to 1000 (one thousand) inclusive were written out
     * in words, how many letters would be used?
     *
     * NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and
     *       forty-two) contains 23 letters and 115 (one hundred and fifteen)
     *       contains 20 letters. The use of "and" when writing out numbers is in
     *       compliance with British usage.
     */
    void Problem17::Solve()
    {
        /**
         * All numbers name less than 20.
         */
        std::string k20FirstNumberNames[] = {
            "zero", "one", "two", "three", "four",
            "five", "six", "seven", "eight", "nine",
            "ten", "eleven", "twelve", "thirteen", "fourteen",
            "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
        };
        /**
         * All numbers name for every 10.
         */
        std::string k10TenthNumberNames[] = {
            "zero", "ten", "twenty", "thirty", "forty",
            "fifty", "sixty", "seventy", "eighty", "ninety"
        };
        uint32_t result = 0;

        for(uint32_t i = 1; i < 1001; ++i)
        {
            std::stringstream number;

            if(i == 1000)
            {
                number << "onethousand";
            }

            // Hundreds
            if(i % 1000 > 99)
            {
                number << k20FirstNumberNames[(i % 1000) / 100] << "hundred";

                if(i % 100 > 0)
                {
                    number << "and";
                }
            }

            // Below one hundred
            if(i % 100 > 0)
            {
                if(i % 100 < 20)
                {
                    number << k20FirstNumberNames[i % 100];
                }
                else
                {
                    number << k10TenthNumberNames[(i % 100) / 10];

                    if(i % 10 > 0)
                    {
                        number << k20FirstNumberNames[i % 10];
                    }
                }
            }

            // Accumulate strings length
            result += number.str().length();
        }

        SetAnswer(result);
    }

}

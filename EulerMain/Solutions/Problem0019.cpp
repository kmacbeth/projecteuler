#include "Problem0019.h"

namespace Euler {



    /**
     * Problem: Counting Sundays
     *
     * You are given the following information, but you may prefer to do some
     * research for yourself.
     *
     * - 1 Jan 1900 was a Monday.
     * - Thirty days has September,
     *   April, June and November.
     *   All the rest have thirty-one,
     *   Saving February alone,
     *   Which has twenty-eight, rain or shine.
     *   And on leap years, twenty-nine.
     * - A leap year occurs on any year evenly divisible by 4, but not on a century
     *   unless it is divisible by 400.
     *
     *   How many Sundays fell on the first of the month during the twentieth
     *   century (1 Jan 1901 to 31 Dec 2000)?
     */
    void Problem19::Solve()
    {
        const uint32_t kMonthDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        const uint32_t kNumberOfMonths = sizeof(kMonthDays) / sizeof(kMonthDays[0]);
        const uint32_t kNumberWeekdays = 7;

        enum Months {
            kJanuary = 0, kFebruary, kMarch, kApril, kMay, kJune,
            kJuly, kSeptember, kOctober, kNovember, kDecember
        };

        enum Days {
            kMonday = 0, kTuesday, kWednesday, kThursday, kFriday, kSaturday, kSunday
        };

        const uint32_t startingYear = 1900;
        const uint32_t endingYear = 2000;

        // Compute leap years
        const uint32_t kLeap4Years = 4;
        const uint32_t kLeap400Years = 400;
        const uint32_t kNoLeap100Years = 100;

        std::vector<uint8_t> leapYears(endingYear + startingYear - 1, 0);

        for (uint32_t year = startingYear; year <= endingYear; ++year)
        {
            if ((year % kLeap400Years == 0) ||
                (year % kLeap4Years == 0 && year % kNoLeap100Years != 0))
            {
                leapYears[year - startingYear] = 1;
            }
            else
            {
                leapYears[year - startingYear] = 0;
            }
        }

        // Find all sunday the first of the month
        uint32_t result = 0;
        uint32_t days = 0; // 01/01/1900 Monday

        for (uint32_t year = startingYear; year <= endingYear; ++year)
        {
            for (uint32_t month = 0; month < kNumberOfMonths; ++month)
            {
                if (year > startingYear && days % kNumberWeekdays == kSunday)
                {
                    ++result;
                }

                days += kMonthDays[month];

                // Adjust february on leap years
                if (leapYears[year - startingYear] && month == kFebruary)
                {
                    ++days;
                }
            }
        }

        SetAnswer(result);
    }

}

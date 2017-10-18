#include "Problem0051.h"
#include "Libs\EulerUtils.h"
#include "Libs\EulerMath.h"
#include "Libs\EratosthenesSieve.h"
#include "Libs\LexicographicPermutation.h"

namespace Euler {

    /**
     * Problem: Prime digit replacements
     *
     * By replacing the 1st digit of the 2-digit number *3, it turns out that
     * six of the nine possible values: 13, 23, 43, 53, 73, and 83, are all 
     * prime.
     *
     * By replacing the 3rd and 4th digits of 56**3 with the same digit, this 
     * 5-digit number is the first example having seven primes among the ten
     * generated numbers, yielding the family: 
     *
     *    56003, 56113, 56333, 56443, 56663, 56773, and 56993. 
     *
     * Consequently 56003, being the first member of this family, is the 
     * smallest prime with this property.
     *
     * Find the smallest prime which, by replacing part of the number (not
     * necessarily adjacent digits) with the same digit, is part of an eight
     * prime value family.
     */
    void Problem51::Solve()
    {
        uint32_t result = 0;
		const uint32_t kLowerBound = 100000;
        const uint32_t kLimit = 1000000;

        // Generate primes
        EulerLib::EratosthenesSieve sieve;
        EulerLib::PrimeSieve::Primes vPrimes;

        sieve(vPrimes, kLimit);

        // Set of prime for fast lookup (test is prime in O(1)
        std::unordered_set<uint32_t> sPrimes(vPrimes.begin(), vPrimes.end());
		std::unordered_set<uint32_t> sNumberDone;

		for (uint32_t number = kLowerBound; number < kLimit; ++number)
		{
			if (sNumberDone.find(number) != sNumberDone.end())
			{
				continue;
			}

			uint32_t maxDigits = EulerLib::CountDigits(number);

			// Convert current number to array
			std::vector<uint32_t> vNumber;
			EulerLib::ToVector(number, vNumber);

			// We are searching a 6-digit number. We can change 1 to 5 digits
			// from the number without touching the least digit.
			for (uint32_t numDigits = 1; numDigits < maxDigits; ++numDigits)
			{
				EulerLib::LexicographicPermutator permute;
				std::vector<uint32_t> vPermutation(maxDigits - 1, 0);

				// The least digit is not included in the possible permutation,
				// this is an important fact from the problem.
				for (uint32_t i = 0; i < numDigits; ++i)
				{
					vPermutation[i] = 1;
				}

				while (permute(vPermutation))
				{
					std::vector<uint32_t> vFoundPrime;

					// For each permutation, replace where 1 is set
					for (uint32_t digit = 0; digit < 10; ++digit)
					{
						if (digit == 0 && vPermutation[0] == 1)
						{
							continue;
						}

						uint32_t newNumber = 0;

						for (uint32_t i = 0; i < maxDigits - 1; ++i)
						{
							if (vPermutation[i])
							{
								newNumber += digit;
							}
							else
							{
								newNumber += vNumber[maxDigits - i - 1];
							}
							newNumber *= 10;
						}

						newNumber += vNumber[0];

						sNumberDone.insert(newNumber);

						if (sPrimes.find(newNumber) != sPrimes.end())
						{
							vFoundPrime.push_back(newNumber);
						}
					}

					if (vFoundPrime.size() >= 8)
					{
						result = vFoundPrime[0];
						goto PRIME_FOUND;
					}
				}
			}
		}

	PRIME_FOUND:
        SetAnswer(result);
    }

}
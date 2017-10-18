#include "Problem0049.h"
#include "Libs\EulerUtils.h"
#include "Libs\EulerMath.h"
#include "Libs\EratosthenesSieve.h"
#include "Libs\LexicographicPermutation.h"

namespace Euler {

    /**
     * Problem: Prime permutations
     *
     * The arithmetic sequence, 1487, 4817, 8147, in which each of the terms 
     * increases by 3330, is unusual in two ways: (i) each of the three terms
     * are prime, and, (ii) each of the 4-digit numbers are permutations of one
     * another.
     *
     * There are no arithmetic sequences made up of three 1-, 2-, or 3-digit 
     * primes, exhibiting this property, but there is one other 4-digit 
     * increasing sequence.
     *
     * What 12-digit number do you form by concatenating the three terms in this
     * sequence?
     */
    void Problem49::Solve()
    {
		const uint32_t kPrimeLimit = 9999;
		const uint32_t kLowerBound = 1001;
		const uint32_t kExcludeNumber = 1487;
        uint64_t result = 0;

        // Generate prime number less than or equal to 4-digits
        EulerLib::EratosthenesSieve sieve;
        EulerLib::PrimeSieve::Primes vPrimes;

        sieve(vPrimes, kPrimeLimit);

        // Ordered set of primes
		std::copy(vPrimes.begin(), vPrimes.end(),
			      std::inserter(m_sPrimes, m_sPrimes.end()));
        
        // For each primes, try to find the sequence
		std::set<uint32_t>::const_iterator itPrime = m_sPrimes.begin();
		bool bFoundSequence = false;

		for (; itPrime != m_sPrimes.end() && !bFoundSequence; ++itPrime)
        {
            if (*itPrime < kLowerBound)
            {
                continue;
            }
    
            // Create permutation of prime number that are primes
            std::vector<uint32_t> vPrimePerms;

            FindPrimePermutations(*itPrime, vPrimePerms);

            // If three or more primes, compute distance between each others
            if (vPrimePerms.size() >= 3 && vPrimePerms[0] != kExcludeNumber)
            {
                std::vector<uint32_t> vPrimeSequence;

                // Find three primes with equal distance, i.e. |p2 - p1| = |p3 - p2|
				bFoundSequence = FindPrimesWithSameDistance(vPrimePerms, vPrimeSequence);
                
				// Concatenate numbers
				if (bFoundSequence)
                {                    
                    for (uint32_t j = 0; j < vPrimeSequence.size(); ++j)
                    {
						result = EulerLib::LeftShift(result, 4);
                        result += vPrimeSequence[j];
                    }
                }
            }
        }

        SetAnswer(result);
    }

    /**
     * Take a prime number and compute all  permutations that are 
	 * prime numbers. 
	 *
	 * @param a_Prime        Current prime number
	 * @param a_rvPrimePerms Prime permutations that are also primes.
     */
    void Problem49::FindPrimePermutations(uint32_t a_Prime, std::vector<uint32_t>& a_rvPrimePerms)
    {
		const uint32_t kNumDigits = 4;
		std::vector<uint32_t> vPermutation(kNumDigits, 0);

        // Convert number to permutation array
        for (uint32_t n = 0; n < kNumDigits; ++n)
        {
			vPermutation[kNumDigits - n - 1] = a_Prime % 10;
			a_Prime /= 10;
        }

        // Find all prime permutations
		EulerLib::LexicographicPermutator permute;

        while (permute(vPermutation))
        {
			// Skip 3-digit numbers (0xyz)
			if (vPermutation[0] == 0)
			{
				continue;
			}

            uint32_t number = EulerLib::ToNumber<uint32_t>(vPermutation);

            // Prime must have 4 digits
            if (m_sPrimes.find(number) != m_sPrimes.end())
            {
				a_rvPrimePerms.push_back(number);
            }
        }
    }

    /**
     * Compute distance between all primes and find three primes with
     * equal distance in between.
	 *
	 * @param a_rvPrimePerms    Vector of permutations that are prime numbers.
	 * @param a_rvPrimeSequence Vector with sequence of primes satisfying distance.
     */
    bool Problem49::FindPrimesWithSameDistance(std::vector<uint32_t>& a_rvPrimePerms,
                                               std::vector<uint32_t>& a_rvPrimeSequence)
    {
		size_t primePermsSize = a_rvPrimePerms.size();
		bool bFound = false;
        uint32_t i = 0;
        uint32_t j = 0;
        uint32_t k = 0;
		
        for (i = 0; i < primePermsSize - 2 && !bFound; ++i)
        {
            uint32_t prime1 = a_rvPrimePerms[i];

            for (j = i + 1; j < primePermsSize - 1 && !bFound; ++j)
            {
                uint32_t prime2 = a_rvPrimePerms[j];

                for (k = j + 1; k < primePermsSize && !bFound; ++k)
                {
                    uint32_t prime3 = a_rvPrimePerms[k];

                    if ((prime3 - prime2) == (prime2 - prime1))
                    {
						bFound = true;
                    }
                }
            }
        }

		a_rvPrimeSequence.push_back(a_rvPrimePerms[i - 1]);
		a_rvPrimeSequence.push_back(a_rvPrimePerms[j - 1]);
		a_rvPrimeSequence.push_back(a_rvPrimePerms[k - 1]);

        return bFound;
    }
}
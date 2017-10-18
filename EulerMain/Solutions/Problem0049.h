#ifndef __EULER_PROBLEM49_H__
#define __EULER_PROBLEM49_H__

#include "Problem.h"
#include "Libs/Euler.h"

namespace Euler {

    class Problem49 : public Problem {

    public:
        Problem49() : Problem("Problem 49") {}

        void Solve();
        
    private:
		std::set<uint32_t> m_sPrimes;
		
		void FindPrimePermutations(uint32_t a_Prime, std::vector<uint32_t>& a_rvPrimePerm);
        bool FindPrimesWithSameDistance(std::vector<uint32_t>& a_rvPrimePerms, 
                                        std::vector<uint32_t>& a_rvPrimeSequence);

    };

}

#endif // __EULER_PROBLEM49_H__
#ifndef __EULER_PROBLEM54_H__
#define __EULER_PROBLEM54_H__

#include "Problem.h"
#include "Problem0054_Hand.h"
#include "Libs/Euler.h"

namespace Euler {

    class Problem54 : public Problem {
        
    public:
        Problem54() : Problem("Problem 54") {}

        void Solve();
        
    private:
        void     GetPlayersHand(std::string& a_rstrline, std::vector<_Problem54::Hand>& a_rHand);
        uint32_t FindRankIndex(const std::string& a_rRank);
        bool     IsValueGreaterThan(const std::string& a_rLhs, const std::string& a_rRhs);

    };

}

#endif // __EULER_PROBLEM54_H__
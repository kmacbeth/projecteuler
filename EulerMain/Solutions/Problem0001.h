#ifndef __EULER_PROBLEM1_H__
#define __EULER_PROBLEM1_H__

#include "Problem.h"
#include "Libs/Euler.h"

namespace Euler {

    class Problem1 : public Problem {

    public:
        Problem1() : Problem("Problem 1") {}

        void Solve();
        
    private:
        uint32_t SumMultipleOfAKind(uint32_t a_Kind, uint32_t a_Limit);
    };

}

#endif // __EULER_PROBLEM1_H__
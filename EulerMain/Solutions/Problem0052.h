#ifndef __EULER_PROBLEM52_H__
#define __EULER_PROBLEM52_H__

#include "Problem.h"
#include "Libs/Euler.h"

namespace Euler {

    class Problem52 : public Problem {

    public:
        Problem52() : Problem("Problem 52") {}

        void Solve();
        
    private:
        bool HasDigitsOccurenceEqual(uint32_t a_X);

    };

}

#endif // __EULER_PROBLEM52_H__
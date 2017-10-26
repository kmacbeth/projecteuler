#ifndef __EULER_PROBLEM${problem_num}_H__
#define __EULER_PROBLEM${problem_num}_H__

#include "Problem.h"
#include "Libs/Euler.h"

namespace Euler {

    class Problem${problem_num} : public Problem {

    public:
        Problem${problem_num}() : Problem("Problem ${problem_num}") {}

        void Solve();

    };

}

#endif // __EULER_PROBLEM${problem_num}_H__
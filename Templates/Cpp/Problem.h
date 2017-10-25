#ifndef __EULER_PROBLEM{_number_}_H__
#define __EULER_PROBLEM{_number_}_H__

#include "Problem.h"
#include "Libs/Euler.h"

namespace Euler {

    class Problem{_number_} : public Problem {

    public:
        Problem{_number_}() : Problem("Problem {_number_}") {}

        void Solve();

    };

}

#endif // __EULER_PROBLEM{_number_}_H__
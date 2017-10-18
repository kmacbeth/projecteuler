#ifndef __EULER_PROBLEM11_H__
#define __EULER_PROBLEM11_H__

#include "Problem.h"
#include "Libs/Euler.h"

namespace Euler {

    class Problem11 : public Problem {

    public:
        Problem11() : Problem("Problem 11") {}

        void Solve();
        
    private:
        struct Direction {
            int32_t m_X;
            int32_t m_Y;
        };
        //typedef std::pair<int32_t, int32_t> Direction;
        typedef std::vector<Direction>      Directions;
    };

}

#endif // __EULER_PROBLEM11_H__
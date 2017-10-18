#ifndef __EULER_PROBLEM29_H__
#define __EULER_PROBLEM29_H__

#include "Problem.h"
#include "Libs/Euler.h"

namespace Euler {

    class Problem29 : public Problem {

    public:
        Problem29() : Problem("Problem 29") {}

        void Solve();

    private:
        /**
         * Power factor keeps track of the Power = Base**Exp.
         */
        struct PowerFactor {
            
            uint32_t m_Power;
            uint32_t m_Exp;

            PowerFactor(uint32_t a_Power, uint32_t a_Exp);
        };
    };

}

#endif // __EULER_PROBLEM29_H__
#ifndef __EULER_PRIMECOUNTER_H__
#define __EULER_PRIMECOUNTER_H__

#include "Euler.h"

namespace EulerLib {

    class PrimeCounter {

    public:
        uint64_t operator()(uint64_t limit);
    };

}

#endif // __EULER_PRIMECOUNTER_H__
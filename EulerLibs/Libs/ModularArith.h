#ifndef __EULER_MODULARARITH_H__
#define __EULER_MODULARARITH_H__

#include "Euler.h"

namespace EulerLib {

    class Modular {

    public:

        static int64_t Add(int64_t a, int64_t b, int64_t modulus);
        static int64_t Sub(int64_t a, int64_t b, int64_t modulus);
        static int64_t Mul(int64_t a, int64_t b, int64_t modulus);
        static int64_t Pow(int64_t a, uint64_t n, int64_t modulus);

    };
}

#endif // __EULER_MODULARARITH_H__
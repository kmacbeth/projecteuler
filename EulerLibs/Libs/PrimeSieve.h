#ifndef __EULER_PRIMESIEVE_H__
#define __EULER_PRIMESIEVE_H__

#include "Euler.h"

namespace EulerLib {

    class PrimeSieve {

    public:
        typedef std::vector<uint32_t> Primes;
        
        virtual void operator()(Primes& a_rPrimes, size_t a_Limit) = 0;
    };

}

#endif // __EULER_PRIMESIEVE_H__
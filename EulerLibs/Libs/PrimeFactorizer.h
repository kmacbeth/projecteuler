#ifndef __EULER_PRIMEFACTORIZER_H__
#define __EULER_PRIMEFACTORIZER_H__

#include "Euler.h"

namespace EulerLib {

    class PrimeFactorizer {

	public:
        struct Factor {
                
            uint64_t m_Base;
            uint32_t m_Exponent;

            Factor();
            Factor(uint64_t a_Base, uint32_t a_Exponent);
        };

		typedef std::vector<Factor> FactorList;

    public:
        PrimeFactorizer();
		    
        void operator()(uint64_t a_Number, FactorList& a_rFactorList);
            
    };

}
#endif // __EULER_PRIMEFACTORIZER_H__

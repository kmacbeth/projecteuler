#ifndef __EULER_DIVISORFUNCTION_H__
#define __EULER_DIVISORFUNCTION_H__

#include "Euler.h"

namespace EulerLib {

	class DivisorFunction {

	public:
        uint64_t operator() (uint64_t a_Number, uint32_t a_KthPower);
	};

}

#endif // __EULER_DIVISORFUNCTION_H__
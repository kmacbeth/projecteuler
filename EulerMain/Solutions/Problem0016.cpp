#include "Problem0016.h"
#include "Libs/EulerMath.h"
#include "Libs/BigInteger.h"

namespace Euler {

    /**
     * Problem: Power digit sum
     *
     * 2**15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
     *
     * What is the sum of the digits of the number 2**1000?
     */
    void Problem16::Solve()
    {
        const uint32_t kExponent = 1000;
        const EulerLib::BigInteger kBase(2);

        // Compute 2**1000
        EulerLib::BigInteger power = EulerLib::Power(kBase, kExponent);

        // Sum all digits
        std::string strNumber = power.ToString();
        size_t strNumberSize = strNumber.size();

        uint64_t result = 0;

        for(size_t i = 0; i < strNumberSize; ++i)
        {
            result += ::atol(strNumber.substr(i, 1).c_str());
        }

        SetAnswer(result);
    }

}

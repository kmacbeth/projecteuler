#include "TestDivisorFunction.h"
#include "Libs/DivisorFunction.h"

namespace EulerTest {

    using namespace EulerLib;

    /**
     * Run tests.
     */
    bool TestDivisorFunction::Run()
    {
        TestFunction();

        return true;
    }

    void TestDivisorFunction::TestFunction()
    {
        std::cout << __FUNCTION__;

        DivisorFunction divisorFunction;
        uint64_t divisorCount = 0;
        uint64_t divisorSum = 0;

        // Divisor function of 6
        divisorCount = divisorFunction(6, 0);
        divisorSum   = divisorFunction(6, 1);

        assert(divisorCount == 4 &&
               "Wrong number of divisors.");
        assert(divisorSum == 12 &&
               "Wrong sum of divisors.");

        // Divisor function of 11
        divisorCount = divisorFunction(11, 0);
        divisorSum   = divisorFunction(11, 1);

        assert(divisorCount == 2 &&
               "Wrong number of divisors.");
        assert(divisorSum == 12 &&
               "Wrong sum of divisors.");

        // Divisor function of 140
        divisorCount = divisorFunction(140, 0);
        divisorSum   = divisorFunction(140, 1);

        assert(divisorCount == 12 &&
               "Wrong number of divisors.");
        assert(divisorSum == 336 &&
               "Wrong sum of divisors.");

        std::cout << "... PASS" << std::endl;
    }

}

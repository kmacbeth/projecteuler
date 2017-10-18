#include "TestPrimeCounter.h"
#include "Libs/PrimeCounter.h"

namespace EulerTest {

    using namespace EulerLib;

    /**
     * Run tests
     */
    bool TestPrimeCounter::Run()
    {
        TestCountPrime();

        return true;
    }

    void TestPrimeCounter::TestCountPrime()
    {
        PrimeCounter countPrime;

        assert(countPrime(1000) == 169);
        assert(countPrime(10000) == 1218);
        assert(countPrime(100000) == 9512);
        assert(countPrime(1000000) == 78030);
    }
};
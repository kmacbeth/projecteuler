#include "TestPrimeFactorizer.h"
#include "Libs/PrimeFactorizer.h"
#include "Libs/Timer.h"

namespace EulerTest {

    using namespace EulerLib;

    /**
     * Run tests.
     */
    bool TestPrimeFactorizer::Run()
    {
        TestFactorization();

        return true;
    }
    
    void TestPrimeFactorizer::TestFactorization()
    {
        std::cout << __FUNCTION__ << std::endl;

        PrimeFactorizer::FactorList factors;
        PrimeFactorizer factorize;

        // Test 1 which is a unit number
        factorize(1, factors);
        assert(factors.size() == 0);

        // Test 2 the only even number to be prime
        factorize(2, factors);
        assert(factors.size() == 1);
        assert(factors[0].m_Base == 2);
        assert(factors[0].m_Exponent == 1);

        // Test 3 the first odd number to be prime
        factorize(3, factors);
        assert(factors.size() == 1);
        assert(factors[0].m_Base  == 3);
        assert(factors[0].m_Exponent == 1);

        // Test 60 = 2 * 2 * 3 * 5
        factorize(60, factors);
        assert(factors.size() == 3);
        assert(factors[0].m_Base  == 2);
        assert(factors[0].m_Exponent == 2);
        assert(factors[1].m_Base  == 3);
        assert(factors[1].m_Exponent == 1);
        assert(factors[2].m_Base  == 5);
        assert(factors[2].m_Exponent == 1);

        // Test 147 = 3 * 7 * 7 which tests n**2 > number
        factorize(147, factors);
        assert(factors.size() == 2);
        assert(factors[0].m_Base  == 3);
        assert(factors[0].m_Exponent == 1);
        assert(factors[1].m_Base  == 7);
        assert(factors[1].m_Exponent == 2);

        // Test 363 = 3 * 11 * 11 which also tests n**2 > number but testing
        // n = 9 which is not prime.
        factorize(363, factors);
        assert(factors.size() == 2);
        assert(factors[0].m_Base  == 3);
        assert(factors[0].m_Exponent == 1);
        assert(factors[1].m_Base  == 11);
        assert(factors[1].m_Exponent == 2);

        // Test 23 which is prime
        factorize(23, factors);
        assert(factors.size() == 1);
        assert(factors[0].m_Base  == 23);
        assert(factors[0].m_Exponent == 1);
    }


    /**
     * Run tests.
     */
    bool PerfPrimeFactorizer::Run()
    {
        TestPerformance();

        return true;
    }
    /**
     * Performance tests.
     */
    void PerfPrimeFactorizer::TestPerformance()
    {
        PrimeFactorizer::FactorList factors;
        PrimeFactorizer factorize;
        Timer timer;

        const uint32_t kNumIterations = 1000;
        double sum = 0.0;

        for(uint32_t i = 0; i < kNumIterations; ++i)
        {
            timer.Start();
            factorize(3439853985334ull, factors);
            timer.Stop();

            sum += timer.GetDeltaTime();
        }

        std::cout << "[INFO] Executing total time: " << sum << " sec" << std::endl;
        std::cout << "[INFO] Number of iterations: " << kNumIterations << std::endl;
        std::cout << "[INFO] Executing average time: " << sum / kNumIterations << " sec" << std::endl;
    }

}
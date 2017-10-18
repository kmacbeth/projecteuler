#include "TestFibonacciSequence.h"
#include "Libs/FibonacciSequence.h"
#include "Libs/BigInteger.h"

namespace EulerTest {

    using namespace EulerLib;

    /**
     * Run test.
     */
    bool TestFibonacciSequence::Run()
    {
        TestFunctorQword();
        TestFunctorBigInteger();
        
        return true;
    }

    /**
     * Test functor returning fibonacci numbers.
     */
    void TestFibonacciSequence::TestFunctorQword()
    {
        std::cout << __FUNCTION__;

        // Test with initial condition (0, 1)
        uint64_t init0Seq[] = {1, 2, 3, 5, 8};
        FibonacciSequence<uint64_t> fib0Seq(0, 1);
        
        for (uint32_t i = 0; i < 5; ++i)
        {
            uint64_t fib = fib0Seq();
            
            assert(fib == init0Seq[i] && "Not a Fibonacci number!");
        }

        // Test with initial condition (1, 1)
        uint64_t init1Seq[] = {2, 3, 5, 8, 13};
        FibonacciSequence<uint64_t> fib1Seq(1, 1);
        
        for (uint32_t i = 0; i < 5; ++i)
        {
            uint64_t fib = fib1Seq();
            
            assert(fib == init1Seq[i] && "Not a Fibonacci number!");
        }

        // Test with initial condition (1, 2)
        uint64_t init2Seq[] = {3, 5, 8, 13, 21};
        FibonacciSequence<uint64_t> fib2Seq(1, 2);
        
        for (uint32_t i = 0; i < 5; ++i)
        {
            uint64_t fib = fib2Seq();
            
            assert(fib == init2Seq[i] && "Not a Fibonacci number!");
        }

        // Test with wrong initial condition (1, 3)
        uint64_t init3Seq[] = {4, 7, 11, 18, 29};
        FibonacciSequence<uint64_t> fib3Seq(1, 3);
        
        for (uint32_t i = 0; i < 5; ++i)
        {
            uint64_t fib = fib3Seq();
            
            assert(fib == init3Seq[i] && "Sequence does not work!");
        }

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test function BigInteger.
     */
    void TestFibonacciSequence::TestFunctorBigInteger()
    {
        std::cout << __FUNCTION__;

        // Test with initial condition (0, 1)
        std::string init0Seq[] = {"1", "2", "3", "5", "8"};
        FibonacciSequence<BigInteger> fib0Seq(0, 1);
        
        for (uint32_t i = 0; i < 5; ++i)
        {
            BigInteger fib = fib0Seq();
            
            assert(fib.ToString() == init0Seq[i] && "Not a Fibonacci number!");
        }

        std::cout << "... PASS" << std::endl;
    }
}
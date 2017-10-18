#include "TestModularArith.h"
#include "Libs/ModularArith.h"

namespace EulerTest {

    using namespace EulerLib;

    /**
     * Run tests.
     */
    bool TestModularArith::Run()
    {
        TestAddition();
        TestSubtraction();
        TestMultiplication();
        TestExponentiation();

        return true;
    }

    void TestModularArith::TestAddition()
    {
        std::cout << __FUNCTION__;

        // Test simple case where modulo is performed on both values
        assert(Modular::Add(12, 11, 3) == 2);

        // Test one argument is zero
        assert(Modular::Add(5, 0, 6) == 5);

        // Test two zerp add up to zero
        assert(Modular::Add(0, 0, 2) == 0);

        // Test one argument smaller than modulus, and other one greater
        assert(Modular::Add(3, 9, 4) == 0);

        std::cout << "... PASS" << std::endl;
    }

    void TestModularArith::TestSubtraction()
    {
        std::cout << __FUNCTION__;

        // Test simple case where modulo is performed on both values
        assert(Modular::Sub(12, 11, 3) == 1);

        // Test one argument is zero
        assert(Modular::Sub(5, 0, 6) == 5);

        // Test two zero subtract to zero
        assert(Modular::Sub(0, 0, 2) == 0);

        // Test one argument smaller than modulus, and other one greater
        assert(Modular::Sub(3, 9, 5) == 4);
        assert(Modular::Sub(9, 3, 5) == 1);

        std::cout << "... PASS" << std::endl;
    }

    void TestModularArith::TestMultiplication()
    {
        std::cout << __FUNCTION__;

        // Test simple case where modulo is performed on both values
        assert(Modular::Mul(12, 11, 3) == 0);

        // Test one argument is zero
        assert(Modular::Mul(5, 0, 6) == 0);

        // Test two zero subtract to zero
        assert(Modular::Mul(0, 0, 2) == 0);

        // Test one argument smaller than modulus, and other one greater
        assert(Modular::Mul(3, 9, 5) == 2);

        // Test one argument is negative
        assert(Modular::Mul(9, -3, 5) == 3);

        std::cout << "... PASS" << std::endl;
    }

    void TestModularArith::TestExponentiation()
    {
        std::cout << __FUNCTION__;

        // Test simple case
        assert(Modular::Pow(9, 9, 100) == 89); 

        // Test case where exponent is zero
        assert(Modular::Pow(3, 0, 2) == 1);

        // Test zero exponent something
        assert(Modular::Pow(0, 2, 2) == 0);

        std::cout << "... PASS" << std::endl;
    }

}

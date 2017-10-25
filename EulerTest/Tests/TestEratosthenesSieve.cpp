#include "TestEratosthenesSieve.h"
#include "Libs/EulerMath.h"
#include "Libs/EratosthenesSieve.h"

namespace EulerTest {

    using namespace EulerLib;

    /**
     * Run tests.
     */
    bool TestEratosthenesSieve::Run()
    {
        TestComputeEratostheneSieve();
        TestComputeSegmentedSieve();
        TestSievingSqrtEqualDelta();

        return true;
    }


    /**
     * All primes below 1000
     */
    const uint32_t TestEratosthenesSieve::kPrimePool[] = {
          2,   3,   5,   7,  11,  13,  17,  19,  23,  29,
         31,  37,  41,  43,  47,  53,  59,  61,  67,  71,
         73,  79,  83,  89,  97, 101, 103, 107, 109, 113,
        127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
        179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
        233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
        283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
        353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
        419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
        467, 479, 487, 491, 499, 503, 509, 521, 523, 541,
        547, 557, 563, 569, 571, 577, 587, 593, 599, 601,
        607, 613, 617, 619, 631, 641, 643, 647, 653, 659,
        661, 673, 677, 683, 691, 701, 709, 719, 727, 733,
        739, 743, 751, 757, 761, 769, 773, 787, 797, 809,
        811, 821, 823, 827, 829, 839, 853, 857, 859, 863,
        877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
        947, 953, 967, 971, 977, 983, 991, 997,1009,1013,
       1019,1021,1031,1033,1039,1049,1051
    };

    /**
     * Test Erathosthene sieving
     */
    void TestEratosthenesSieve::TestComputeEratostheneSieve()
    {
        std::cout << __FUNCTION__;

        // Find all primes below 100, delta = 32768 will force erathostene
        EratosthenesSieve eraSieve;
        PrimeSieve::Primes vPrimes;

        eraSieve(vPrimes, 100);

        assert(vPrimes.size() == 25);

        for(size_t i = 0; i < vPrimes.size(); ++i)
        {
            assert(vPrimes[i] == kPrimePool[i]);
        }

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test segmented sieving
     */
    void TestEratosthenesSieve::TestComputeSegmentedSieve()
    {
        std::cout << __FUNCTION__;

        PrimeSieve::Primes vPrimes;

        // Find all primes below 1000, delta = 11 will force segmentation
        EratosthenesSieve segSieve(11);

        segSieve(vPrimes, 1000);

        assert(vPrimes.size() == 168);

        for(size_t i = 0; i < vPrimes.size(); ++i)
        {
            assert(vPrimes[i] == kPrimePool[i]);
        }

        // Find all primes below 1060
        EratosthenesSieve bugSieve(11);

        bugSieve(vPrimes, 1060);

        assert(vPrimes.size() == 177);

        for(size_t i = 0; i < vPrimes.size(); ++i)
        {
            assert(vPrimes[i] == kPrimePool[i]);
        }

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test segmented sieving with sqrt(n) == delta
     */
    void TestEratosthenesSieve::TestSievingSqrtEqualDelta()
    {
        std::cout << __FUNCTION__;

        PrimeSieve::Primes vPrimes;

        // Test sqrt(n) = delta for delta is composite
        EratosthenesSieve sieve1(10);

        sieve1(vPrimes, 100);

        assert(vPrimes.size() == 25);

        for(size_t i = 0; i < vPrimes.size(); ++i)
        {
            assert(vPrimes[i] == kPrimePool[i]);
        }

        // Test sqrt(n) = delta for delta is prime
        EratosthenesSieve sieve2(13);

        sieve2(vPrimes, 169);

        assert(vPrimes.size() == 39);

        for(size_t i = 0; i < vPrimes.size(); ++i)
        {
            assert(vPrimes[i] == kPrimePool[i]);
        }

        std::cout << "... PASS" << std::endl;
    }
}
#include "EratosthenesSieve.h"
#include "EulerMath.h"

namespace EulerLib {

    /**
     * Sive of Erathosthenes constructor.
     *
     * @param a_Limit Superior limit where to stop generating primes.
     * @param a_Delta Segment size for the segmented sieve.
     */
    EratosthenesSieve::EratosthenesSieve(size_t a_Delta) :
        m_Limit(0),
        m_SqrtLimit(0),
        m_Delta(a_Delta)
    {
    }

    /**
     * Generate the primes number between [2, limit_]
     */
    void EratosthenesSieve::operator()(Primes& a_rPrimes, size_t a_Limit)
    {
        m_Limit = a_Limit;
        m_SqrtLimit = EulerLib::SquareRoot(a_Limit);

        a_rPrimes.clear();

        if(m_Limit < m_Delta)
        {
            ComputeOptimizedEraSieve(a_rPrimes, m_Limit);
        }
        else
        {
            ComputeSegmentedSieve(a_rPrimes);
        }
    }

    /**
     * Compute optimized sieve of Erathostene
     *
     * @param a_Limit Current limit to generate primes.
     *
     * @note Reference: https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes#Pseudocode
     */
    void EratosthenesSieve::ComputeOptimizedEraSieve(Primes& a_rPrimes, size_t a_Limit)
    {
        // Sieve only odd number
        Sieve  bvSieve(a_Limit / 2 + (a_Limit & 0x1), true);
        size_t limitOdd = a_Limit - (a_Limit & 0x1 ? 0 : 1);
    
        for(uint32_t i = 1, p = 2 * i + 1; p * p <= limitOdd; ++i, p += 2)
        {
            if(bvSieve[i])
            {
                for(uint32_t j = p * p; j <= limitOdd; j += p << 1)
                {
                    bvSieve[(j - 1) >> 1] = false;
                }
            }
        }

        // Reset prime list
        a_rPrimes.clear();

        // Add 2 since even number were not accounted
        a_rPrimes.push_back(2);

        // Number 1 is not prime, but unit
        for(size_t i = 1; i < bvSieve.size(); ++i)
        {
            if(bvSieve[i])
            {
                a_rPrimes.push_back(2 * i + 1);
            }
        }
    }

    /**
     * Compute segmented sieve of primes
     *
     * Reference: https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes#Segmented_sieve
     */
    void EratosthenesSieve::ComputeSegmentedSieve(Primes& a_rPrimes)
    {
        // Compute prime number from [2, sqrt(n)]   
        ComputeOptimizedEraSieve(a_rPrimes, m_SqrtLimit);

        size_t maxSievingPrime = a_rPrimes.size();

        // Compute segments
        size_t segmentSize = (m_Delta < m_SqrtLimit ? m_Delta : m_SqrtLimit);   

        for(uint32_t lowBound = m_SqrtLimit; lowBound < m_Limit; lowBound += segmentSize)
        {
            Sieve    bvSieve(segmentSize, true);
            uint32_t highBound = std::min(lowBound + segmentSize - 1, m_Limit);

            for(uint32_t p = 0; p < maxSievingPrime; ++p)
            {
                // Get sieving prime and align on the segment first multiple of prime
                uint32_t prime  = a_rPrimes[p];
                uint32_t number = (lowBound / prime * prime) + 
                                  (lowBound % prime != 0 ? prime : 0 );

                // For each multiple of prime in segment mark as composite
                for(uint32_t n = number; n <= highBound; n += prime)
                {
                    bvSieve[n - lowBound] = false;
                }
            }

            for(size_t n = lowBound; n <= highBound; ++n)
            {
                if(bvSieve[n - lowBound])
                {
                    a_rPrimes.push_back(n);
                }
            }
        }
    }

}
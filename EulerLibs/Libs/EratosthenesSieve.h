#ifndef __EULER_ERATOSTHENESSIEVE_H__
#define __EULER_ERATOSTHENESSIEVE_H__

#include "Euler.h"
#include "PrimeSieve.h"

namespace EulerLib {

	class EratosthenesSieve : public PrimeSieve {

	public:
		EratosthenesSieve(size_t a_Delta = kL1CacheSize);

		void operator()(Primes& a_rPrimes, size_t a_Limit);

	private:
		typedef std::vector<bool> Sieve; 

		static const uint32_t kL1CacheSize = 32768;
    
    private:
		void ComputeOptimizedEraSieve(Primes& a_rPrimes, size_t a_Limit);
		void ComputeSegmentedSieve(Primes& a_rPrimes);

		uint32_t m_Limit;
		uint32_t m_SqrtLimit;
		uint32_t m_Delta;
	};

}

#endif // __EULER_ERATOSTHENESSIEVE_H__
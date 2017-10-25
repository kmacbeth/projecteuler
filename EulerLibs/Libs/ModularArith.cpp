#include "ModularArith.h"
#include "EulerMath.h"

namespace EulerLib {

    /**
     * Modular Addition.
     *
     * (a + b) mod c = (a mod c + b mod c) mod c
     */
    int64_t Modular::Add(int64_t a, int64_t b, int64_t modulus)
    {
        int64_t ap = EulerLib::Modulus(a, modulus);
        int64_t bp = EulerLib::Modulus(b, modulus);

        return EulerLib::Modulus(ap + bp, modulus);
    }

    /**
     * Modular Subtraction.
     *
     * (a - b) mod c = (a mod c - b mod c) mod c
     */
    int64_t Modular::Sub(int64_t a, int64_t b, int64_t modulus)
    {
        return Add(a, -b, modulus);
    }

    /**
     * Modular Multiplication.
     *
     * (a * b) mod c = (a mod c * b mod c) mod c
     */
    int64_t Modular::Mul(int64_t a, int64_t b, int64_t modulus)
    {
        int64_t ap = EulerLib::Modulus(a, modulus);
        int64_t bp = EulerLib::Modulus(b, modulus);

        return EulerLib::Modulus(ap * bp, modulus);
    }

    /**
     * Modular Exponentiation.
     *
     * (a**n) mod c = ((a mod c)**n mod c)
     *              = (((a mod c) * a mod c) * a mod c)
     */
    int64_t Modular::Pow(int64_t a, uint64_t n, int64_t modulus)
    {
        if (n == 0) return 1;

        int64_t value = a;

        for (uint32_t i = 1; i < n; ++i)
        {
            value = EulerLib::Modulus(value * a, modulus);
        }

        return value;
    }
}
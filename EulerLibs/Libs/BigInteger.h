#ifndef __EULER_BIGINTEGER_H__
#define __EULER_BIGINTEGER_H__

#include "Euler.h"

namespace EulerTest {

    class TestBigInteger;
}

namespace EulerLib {

    /**
     * BigInteger:
     *
     * This is a BigInteger class that handle large numbers > 2**64-1.
     * Most operator used with integer are defined.
     *
     * @note For the moment, only unsigned numbers are supported
     */
	class BigInteger {
    
    public:
        friend void swap(BigInteger& a_rLhs, BigInteger& a_rRhs);

        friend bool          operator< (const BigInteger& a_rLhs, const BigInteger& a_rRhs);
        friend bool          operator==(const BigInteger& a_rLhs, const BigInteger& a_rRhs);
        friend std::ostream& operator<<(std::ostream& a_rStream, const BigInteger& a_rBigNumber);

        friend class EulerTest::TestBigInteger;

    public:      

        BigInteger();
        BigInteger(uint64_t a_Number);
        BigInteger(const std::string& a_rStrNumber);
		BigInteger(const BigInteger& a_rOther);

        ~BigInteger();

		// Reference: http://stackoverflow.com/questions/4421706/operator-overloading/4421729
		BigInteger operator= (BigInteger a_Other);

		BigInteger& operator+=(const BigInteger& a_rOther);
		BigInteger& operator-=(const BigInteger& a_rOther);
		BigInteger& operator*=(const BigInteger& a_rOther);
		BigInteger& operator/=(const BigInteger& a_rOther);
        BigInteger& operator%=(const BigInteger& a_rOther);

        void FromString(const std::string& a_rStrNumber);
        std::string ToString() const;

    private:
        typedef std::vector<uint64_t> BinVector;

	private:
        void FromDecString(const std::string& a_rStrNumber);
        void FromHexString(const std::string& a_rStrNumber);

        uint64_t AddBins(uint64_t a_BinLeft, uint64_t a_BinRight, uint64_t& a_rCarry);

        BinVector m_vBins;
	};

    /**
     * Operator greater than.
     *
     * @param a_rLhs Reference to left-hand side of the operator
     * @param a_rRhs Reference to left-hand side of the operator
     *
     * @return Returns 'true' when greater, otherwise 'false'.
     */
    inline bool operator> (const BigInteger& a_rLhs, const BigInteger& a_rRhs)
    {
        return operator< (a_rRhs, a_rLhs);
    }

    /**
     * Operator smaller than or equals.
     *
     * @param a_rLhs Reference to left-hand side of the operator
     * @param a_rRhs Reference to left-hand side of the operator
     *
     * @return Returns 'false' when greater, otherwise 'true'.
     */
    inline bool operator<=(const BigInteger& a_rLhs, const BigInteger& a_rRhs)
    {
        return !operator> (a_rLhs, a_rRhs);
    }

    /**
     * Operator greater than or equals.
     *
     * @param a_rLhs Reference to left-hand side of the operator
     * @param a_rRhs Reference to left-hand side of the operator
     *
     * @return Returns 'false' when smaller, otherwise 'true'.
     */
    inline bool operator>=(const BigInteger& a_rLhs, const BigInteger& a_rRhs)
    {
        return !operator< (a_rLhs, a_rRhs);
    }

    /**
     * Operator not equals.
     *
     * @param a_rLhs Reference to left-hand side of the operator
     * @param a_rRhs Reference to left-hand side of the operator
     *
     * @return Returns 'false' when equals, otherwise 'true'.
     */
    inline bool operator!=(const BigInteger& a_rLhs, const BigInteger& a_rRhs)
    {
        return !operator==(a_rLhs, a_rRhs);
    }

	inline BigInteger operator+ (BigInteger a_Lhs, const BigInteger& a_rRhs)
	{
		a_Lhs += a_rRhs;
		return a_Lhs;
	}

	inline BigInteger operator- (BigInteger a_Lhs, const BigInteger& a_rRhs)
	{
		a_Lhs -= a_rRhs;
		return a_Lhs;
	}

	inline BigInteger operator* (BigInteger a_Lhs, const BigInteger& a_rRhs)
	{
		a_Lhs *= a_rRhs;
		return a_Lhs;
	}

	inline BigInteger operator/ (BigInteger a_Lhs, const BigInteger& a_rRhs)
	{
		a_Lhs /= a_rRhs;
		return a_Lhs;
	}

}

#endif // __EULER_BIGINTEGER_H__
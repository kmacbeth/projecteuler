#include "BigInteger.h"

namespace EulerLib {

    /**
     * Default constructor.
     */
    BigInteger::BigInteger() :
        m_vBins()
    {
    }

    /**
     * Copy constructor.
     *
     * @param a_rOther Reference to the object to copy from.
     */
    BigInteger::BigInteger(const BigInteger& a_rOther) :
        m_vBins(a_rOther.m_vBins)
    {
    }

    /**
     * Specialized constructor for unsigned integers.
     *
     * @param a_Number Unsigned integer number.
     *
     * @note Taking an unsigned long long argument allows to use any type of unsigned
     *       integer, as the integer will be promoted to unsigned long long during
     *       argument conversion.
     */
    BigInteger::BigInteger(uint64_t a_Number) :
        m_vBins()
    {
        m_vBins.push_back(a_Number);
    }

    /**
     * Specialized constructor for string numbers.
     *
     * @param a_rStrNumber Reference to a string containing a large number.
     */
    BigInteger::BigInteger(const std::string& a_rStrNumber) :
        m_vBins()
    {
        FromString(a_rStrNumber);
    }

    /**
     * Default destructor.
     */
    BigInteger::~BigInteger()
    {
    }

    /**
     * Overload operator equals '='
     *
     * @param a_rOther Reference to the object to equal to.
     *
     * @return Copy of the current object.
     */
    BigInteger BigInteger::operator= (BigInteger a_Other)
    {
        swap(*this, a_Other);

        return *this;
    }

    /**
     * Operator add-assign
     *
     * @param a_rOther Reference to the BigInteger to add
     *
     * @return Reference to the current BigInteger.
     */
    BigInteger& BigInteger::operator+=(const BigInteger& a_rOther)
    {
        // TODO: consider non-const pass-by value instead of creating a new copy
        BigInteger bigOther(a_rOther);
        uint32_t   largestSize  = m_vBins.size();
        uint32_t   smallestSize = bigOther.m_vBins.size();

        // Just swap the copies to keep the algorithm cleaner
        if (smallestSize > largestSize)
        {
            std::swap(smallestSize, largestSize);
            std::swap(bigOther.m_vBins, m_vBins);
        }

        // Apply the sum of both BigInteger
        uint64_t carry = 0;

        m_vBins.resize(largestSize); // Will be at least the largest size

        // Sum common bins
        for (uint32_t i = 0; i < smallestSize; ++i)
        {
            m_vBins[i] = AddBins(m_vBins[i], bigOther.m_vBins[i], carry);
        }
        // Add carry over the remaining bins
        for (uint32_t i = smallestSize; i < largestSize; ++i)
        {
            m_vBins[i] = AddBins(m_vBins[i], 0, carry);
        }
        // Carry over, we need to push it into a new bin
        if (carry > 0)
        {
            m_vBins.push_back(carry);
        }

        return *this;
    }

    BigInteger& BigInteger::operator-=(const BigInteger& other)
    {
        return *this;
    }

    /**
     * Operator multiply-assign
     *
     * @param a_rOther Reference to the BigInteger to add
     *
     * @return Reference to the current BigInteger.
     */
    BigInteger& BigInteger::operator*=(const BigInteger& a_rOther)
    {
        BigInteger bigOther(a_rOther);
        uint32_t   largestSize  = m_vBins.size();
        uint32_t   smallestSize = bigOther.m_vBins.size();

        // multiplicand * multiplier, where multiplicand (m_vBins)is always the larger
        if (smallestSize > largestSize)
        {
            std::swap(smallestSize, largestSize);
            std::swap(bigOther.m_vBins, m_vBins);
        }

        /*
         *  This is how we multiply two uint64_t without loosing the bits
         *  past the 64th bit:
         *
         *  63    31    0    63    31    0
         *  +-----+-----+    +-----+-----+
         *  |  a  |  b  |    |  c  |  d  |
         *  +-----+-----+    +-----+-----+
         *
         *  127   95    63    31    0
         *  +-----+-----+-----+-----+
         *  |           |           |
         *  +-----+-----+-----+-----+
         *  |--- ac  ---|--- bd  ---|
         *        |--- ad  ---|
         *        |--- bc  ---|
         *
         *  (a<<32 + b) * (c<<32 + d) = ac<<64 + ad<<32 + bc<<32 + bd
         */
        std::vector<uint64_t> vProduct(smallestSize + largestSize);

        for (uint32_t i = 0; i < smallestSize; ++i)
        {
            for (uint32_t j = 0; j < largestSize; ++j)
            {
                uint64_t a = m_vBins[j] >> 32;
                uint64_t b = m_vBins[j] & 0xFFFFFFFF;
                uint64_t c = bigOther.m_vBins[i] >> 32;
                uint64_t d = bigOther.m_vBins[i] & 0xFFFFFFFF;

                uint64_t ac = a * c;
                uint64_t ad = a * d;
                uint64_t bc = b * c;
                uint64_t bd = b * d;

                uint64_t carry = 0;

                bd = AddBins((bc & 0xFFFFFFFF) << 32, bd, carry);
                bd = AddBins((ad & 0xFFFFFFFF) << 32, bd, carry);

                ac = AddBins(bc >> 32 , ac, carry);
                ac = AddBins(ad >> 32 , ac, carry);

                vProduct[j + i]     = AddBins(vProduct[j + i],     bd, carry);
                vProduct[j + i + 1] = AddBins(vProduct[j + i + 1], ac, carry);

                if (carry != 0)
                {
                    vProduct[j + i + 2] = carry;
                }
            }
        }

        // Remove last bin set to zero
        if (vProduct.back() == 0)
        {
            vProduct.pop_back();
        }

        std::swap(m_vBins, vProduct);

        return *this;
    }

    BigInteger& BigInteger::operator/=(const BigInteger& other)
    {
        return *this;
    }

    BigInteger& BigInteger::operator%=(const BigInteger& other)
    {
        return *this;
    }

    /**
     * Build a BigInteger from a string number.
     *
     * @param a_rStrNumber Reference to the string number.
     */
    void BigInteger::FromString(const std::string& a_rStrNumber)
    {
        // Check whether we have an hexstring number.
        // If it is way faster to process.
        if (a_rStrNumber.substr(0, 2) == "0x")
        {
            FromHexString(a_rStrNumber);
        }
        else
        {
            FromDecString(a_rStrNumber);
        }
    }

    /**
     * Convert BigInteger into a string number.
     *
     * @return String containing the number.
     */
    std::string BigInteger::ToString() const
    {
        uint32_t binSize = m_vBins.size();

        if (binSize == 0)
        {
            return std::string("");
        }

        std::vector<uint32_t> digits(1, 0);

        for (uint32_t i = 0; i < binSize; ++i)
        {
            uint64_t bin = m_vBins[binSize - 1 - i];

            for (uint32_t b = 0; b < 64; ++b)
            {
                uint32_t digitsSize = digits.size();

                // Multiply by two
                for (uint32_t d = 0; d < digitsSize; ++d)
                {
                    digits[d] <<= 1;
                }
                // Propagate carry to higher-order digits
                for (uint32_t d = 0; d < digitsSize - 1; ++d)
                {
                    digits[d + 1] += digits[d] / 10;
                    digits[d] %= 10;
                }
                // Propagate carry out of current number
                if (digits[digitsSize - 1] > 9)
                {
                    digits.push_back(digits[digitsSize - 1] / 10);
                    digits[digitsSize - 1] %= 10;
                }

                digits[0] += ((bin >> (63 - b)) & 0x1);
            }
        }

        // Convert number to string
        std::ostringstream strNumber;
        uint32_t digitsSize = digits.size();

        for (uint32_t i = 0; i < digitsSize; ++i)
        {
            strNumber << digits[digitsSize - 1 - i];
        }

        return strNumber.str();
    }

    /**
     * Build a BigInteger from a decimal string number.
     *
     * @param a_rStrNumber Reference to the string number.
     */
    void BigInteger::FromDecString(const std::string& a_rStrNumber)
    {
        uint32_t strSize = a_rStrNumber.size();

        // String -> Array of digits
        std::vector<uint32_t> digits;

        for (uint32_t i = 0; i < strSize; ++i)
        {
            uint32_t digitValue = std::strtoul(a_rStrNumber.substr(strSize - i - 1, 1).c_str(), NULL, 0);
            digits.push_back(digitValue);
        }

        /*
         * Convert from base 10 digit array to binary:
         * Take last bit and save it. Divide by 2 and repeat until
         * number is zero.
         */
        uint64_t bin = 0;
        uint32_t shift = 0;

        while (!digits.empty())
        {
            uint64_t firstDigit = static_cast<uint64_t>(digits.front());

            // Check we've reached 64 bit shifts
            if ((shift & 0x40) == 0x40)
            {
                m_vBins.push_back(bin);
                shift = 0;
                bin = 0;
            }

            // Check first bit and move to bin
            bin |= (firstDigit & 0x1) << shift++;

            // Divide by 2 algorithm
            std::vector<uint32_t> reminders(digits);

            std::fill(digits.begin(), digits.end(), 0ul);

            while (!reminders.empty())
            {
                bool isNonZero = false;

                // Divide by two each digit and subtract to get remainders
                for (uint32_t i = 0; i < reminders.size(); ++i)
                {
                    uint32_t quotient = reminders[i] >> 1;

                    digits[i] += quotient;
                    reminders[i] = reminders[i] - (quotient << 1);

                    // Check when reminders are all zeros
                    isNonZero |= !!reminders[i];
                }

                // Check for early exit when all remainders are zero,
                // which can speed up quite a bit on very large numbers.
                if (!isNonZero)
                {
                    break;
                }

                // Move remainder carry down
                for (uint32_t i = 0; i < reminders.size() - 1; ++i)
                {
                    reminders[i] = 0;
                    reminders[i] += reminders[i + 1] * 10;
                }

                // Remove digit set to zero
                reminders.pop_back();
            }

            // Remove leading zeroes
            uint32_t digitSize = digits.size();

            for (uint32_t i = 0; i < digitSize && digits[digitSize - i - 1] == 0; ++i)
            {
                digits.pop_back();
            }
        }

        m_vBins.push_back(bin);
    }

    /**
     * Build a BigInteger from a hexadecimal string number.
     *
     * @param a_rStrNumber Reference to the hexstring number.
     */
    void BigInteger::FromHexString(const std::string& a_rStrNumber)
    {
        uint32_t remStrSize = a_rStrNumber.size() - 2;
        uint32_t numHexChunk = ((remStrSize - 1) / 8) + 1;
        uint64_t bin = 0x0;

        for (uint32_t i = 0; i < numHexChunk; ++i)
        {
            uint32_t curChunkSize = remStrSize < 8 ? remStrSize : 8;

            // The string is walked backward from the end, a chuck is 8 characters (DWORD)
            // or less at the end of the number:
            //    remStrSize + 2 -> Sets us at the end of the chunk
            //    - curChunkSize -> Sets us at the start of the chunk
            std::string chunk = a_rStrNumber.substr(remStrSize + 2 - curChunkSize, curChunkSize);

            // Split into 2 32-bit chunks (VS2012 does not not support strtoull)
            if ((i & 0x1) == 0x1)
            {
                bin |= static_cast<uint64_t>(std::strtoul(chunk.c_str(), NULL, 16)) << 32;
                m_vBins.push_back(bin);
            }
            else
            {
                bin = static_cast<uint64_t>(std::strtoul(chunk.c_str(), NULL, 16));
            }

            remStrSize -= curChunkSize;
        }

        // Since chunks are pushed every two chunks, we must finish
        // the half bin (1 chunk) by pushing it also.
        if ((numHexChunk & 0x1) == 0x1)
        {
            m_vBins.push_back(bin);
        }
    }

    /**
     * Add two bins together.
     *
     * @param a_BinLhs The left-hand bin for addition.
     * @param a_BinRhs The right-hand bin for addition.
     * @param a_rBinResult The bin addition result.
     */
    uint64_t BigInteger::AddBins(uint64_t a_BinLhs, uint64_t a_BinRhs, uint64_t& a_rCarry)
    {
        // Add carry in into lower DWORD
        uint64_t dwLower = (a_BinLhs & 0xFFFFFFFF) + (a_BinRhs & 0xFFFFFFFF) + a_rCarry;
        // Carry over from lower DWORD to upper DWORD
        uint64_t dwUpper = (a_BinLhs >> 32) + (a_BinRhs >> 32) + (dwLower >> 32);

        // Keep any carry over the upper DWORD
        a_rCarry = dwUpper >> 32;

        // Remove residual carry
        return ((dwUpper & 0xFFFFFFFF) << 32) | (dwLower & 0xFFFFFFFF);
    }

    /**
     * Swap two BigIntegers.
     *
     * @param a_rLhs Left-hand side to swap
     * @param a_rRhs Right-hand side to swap
     */
    void swap(BigInteger& a_rLhs, BigInteger& a_rRhs)
    {
        using std::swap;

        swap(a_rLhs.m_vBins, a_rRhs.m_vBins);
    }

    /**
     * Operator smaller than.
     *
     * @param a_rLhs Reference to left-hand side of the operator
     * @param a_rRhs Reference to left-hand side of the operator
     *
     * @return Returns 'true' when smaller, otherwise 'false'.
     */
    bool operator< (const BigInteger& a_rLhs, const BigInteger& a_rRhs)
    {
        // When the number of bin is different, we know the result
        if (a_rLhs.m_vBins.size() != a_rRhs.m_vBins.size())
        {
            return (a_rLhs.m_vBins.size() < a_rRhs.m_vBins.size());
        }

        // Otherwise, the same number of bins, check most significant bins
        uint32_t lhsSize = a_rLhs.m_vBins.size();

        for (uint32_t i = 0; i < lhsSize; ++i)
        {
            if (a_rLhs.m_vBins[lhsSize - 1 - i] < a_rRhs.m_vBins[lhsSize - 1 - i])
            {
                return true;
            }
            else if (a_rLhs.m_vBins[lhsSize - 1 - i] > a_rRhs.m_vBins[lhsSize - 1 - i])
            {
                return false;
            }
        }

        return false;
    }

    /**
     * Operator equals.
     *
     * @param a_rLhs Reference to left-hand side of the operator
     * @param a_rRhs Reference to left-hand side of the operator
     *
     * @return Returns 'true' when equal, otherwise 'false'.
     */
    bool operator==(const BigInteger& a_rLhs, const BigInteger& a_rRhs)
    {
        // When the number of bin is different, we know the result
        if (a_rLhs.m_vBins.size() != a_rRhs.m_vBins.size())
        {
            return false;
        }

        // Otherwise, the same number of bins, check most significant bins
        uint32_t lhsSize = a_rLhs.m_vBins.size();

        for (uint32_t i = 0; i < lhsSize; ++i)
        {
            if (a_rLhs.m_vBins[lhsSize - 1 - i] != a_rRhs.m_vBins[lhsSize - 1 - i])
            {
                return false;
            }
        }

        // Both numbers are equal
        return true;
    }

    /**
     * Overload << to print the big integer in string number.
     *
     * @param a_rStream    A stream object to write to.
     * @param a_rBigNumber Reference to a BigInteger instance to display.
     *
     * @return The newly written stream object.
     */
    std::ostream& operator<<(std::ostream& a_rStream, const BigInteger& a_rBigNumber)
    {
        a_rStream << a_rBigNumber.ToString();

        return a_rStream;
    }
}

#ifndef __EULER_UTILS_H__
#define __EULER_UTILS_H__

#include "Euler.h"

namespace EulerLib {

    /**
     * Open a file and read all line into a vector.
     */
    bool ReadFile(std::string& a_rstrFilename, std::vector<std::string>& a_rvLines);

    /**
     * Tokenize a string (as a line)
     */
    void Tokenize(std::string& a_rstrLine,
                  std::vector<std::string>& a_rvTokens,
                  char a_Delimiter);

    /**
     * Convert to number.
     *
     * Type T must implement += and *=. The function does not check
     * for any overflow. E.g. pushing 56789012345 will not result in
     * 789012345 for a uint32_t.
     *
     * @param a_rContainer A vector object containing digits
     *
     * @return Number using template type.
     */
    template<typename T> inline T ToNumber(std::vector<uint32_t>& a_rContainer)
    {
        T number = 0;
        size_t numElements = a_rContainer.size();

        for(uint32_t i = 0; i < numElements; ++i)
        {

            number *= 10;
            number += a_rContainer[i];
        }

        return number;
    }

    /**
     * Convert to vector.
     *
     * Type T must implement /= and %=.
     *
     * @param a_Number     Number to convert into vector of digits
     * @param a_rContainer A vector object containing digits
     */
    template<typename T> inline void ToVector(T a_Number, std::vector<uint32_t>& a_rContainer)
    {
        while (a_Number > 0)
        {
            a_rContainer.push_back(a_Number % 10);
            a_Number /= 10;
        }
    }

}

#endif // __EULER_UTILS_H__
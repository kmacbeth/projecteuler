#include "LexicographicPermutation.h"
#include "EulerMath.h"

namespace EulerLib {

    /**
     * Default constructor with default argument.
     *
     * @param a_bFirstPermutation Indicate we do first permutation.
     */
    LexicographicPermutator::LexicographicPermutator(bool a_bFirstPermutation) :
        m_bFirstPermutation(a_bFirstPermutation)
    {
    }

    /**
     * Perform a permutation.
     *
     * @param a_rElement A vector object of numbers.
     *
     * @return Returns true until no more permutation can be done.
     *
     * @note Reference: https://www.nayuki.io/page/next-lexicographical-permutation-algorithm
     */
    bool LexicographicPermutator::operator()(std::vector<uint32_t>& a_rvElements)
    {
        // First permutation is the one passed in the array.
        if (m_bFirstPermutation)
        {
            m_bFirstPermutation = false;
            std::sort(a_rvElements.begin(), a_rvElements.end());

            return true;
        }

        uint32_t first = a_rvElements.front();
        uint32_t last = a_rvElements.back();

        // Single permutation
        uint32_t numElements = a_rvElements.size();
        uint32_t i = numElements - 1;
        uint32_t j = numElements - 1;

        // Find largest index with increment
        while(i > 0 && a_rvElements[i - 1] >= a_rvElements[i])
        {
            --i;
        }

        if (i < 1)
        {
            return false;
        }

        // Find largest index with decrement
        while(a_rvElements[j] <= a_rvElements[i - 1])
        {
            --j;
        }

        std::swap(a_rvElements[i - 1], a_rvElements[j]);

        // Reverse suffix
        for(j = numElements - 1; i < j; ++i, --j)
        {
            std::swap(a_rvElements[i], a_rvElements[j]);
        }

        return true;
    }
}
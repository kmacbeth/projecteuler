#ifndef __EULER_LEXICOGRAPHICPERMUTATION_H__
#define __EULER_LEXICOGRAPHICPERMUTATION_H__

#include "Euler.h"

namespace EulerLib {

    class LexicographicPermutator {

    public:
        LexicographicPermutator(bool m_bFirstPermutation = true);

        bool operator()(std::vector<uint32_t>& a_rElements);

    private:
        bool m_bFirstPermutation;

    };

}

#endif // __EULER_LEXICOGRAPHICPERMUTATION_H__
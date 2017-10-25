#include "Problem0042.h"
#include "Libs/EulerMath.h"
#include "Libs/EulerUtils.h"

namespace Euler {

    /**
     * Problem: Coded triangle numbers
     *
     * The nth term of the sequence of triangle numbers is given by,
     * t_n = ½n(n+1); so the first ten triangle numbers are:
     *
     * 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
     *
     * By converting each letter in a word to a number corresponding to its
     * alphabetical position and adding these values we form a word value. For
     * example, the word value for SKY is 19 + 11 + 25 = 55 = t10. If the word
     * value is a triangle number then we shall call the word a triangle word.
     *
     * Using words.txt (right click and 'Save Link/Target As...'), a 16K text
     * file containing nearly two-thousand common English words, how many are
     * triangle words?
     */
    void Problem42::Solve()
    {
        // The file is a single line containing names CSV-style:
        // "NAME1","NAME2",...,"NAMEX"
        std::string strFilename = "../Data/Euler/p042_words.txt";
        std::vector<std::string> vLines;

        EulerLib::ReadFile(strFilename, vLines);

        // Get all names
        std::vector<std::string> vNames;

        EulerLib::Tokenize(vLines[0], vNames, ',');

        // Largest non-technical word in english has 29 letters.
        // So we need to generate triangular number until (29 * 26) = 754;
        // Which would be 29 times letter 'z'. Precomputing now, avoids
        // doing it later on every number.
        const uint32_t kMaxTriangularNumber = 754;
        std::set<uint32_t> triangularNumber;

        for (uint32_t i = 1; i <= kMaxTriangularNumber; ++i)
        {
            triangularNumber.insert((i * (i + 1)) >> 1);
        }

        // Compute number for each word, and if it is a triangular number
        // count it.
        const uint8_t kLetterAOffset = 65;
        uint32_t namesSize = vNames.size();
        uint32_t result = 0;

        for (size_t i = 0; i < namesSize; ++i)
        {
            uint32_t nameSize = vNames[i].size();
            uint32_t total = 0;

            for (size_t s = 1; s < nameSize - 1; ++s)
            {
                // Remove '"'s
                total += vNames[i][s] - kLetterAOffset + 1;
            }

            if (triangularNumber.find(total) != triangularNumber.end())
            {
                ++result;
            }
        }

        SetAnswer(result);
    }
}
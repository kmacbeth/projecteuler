#include "Problem0022.h"
#include "Libs/EulerUtils.h"

namespace Euler {

    /**
     * Problem: Names scores
     *
     * Using names.txt, a 46K text file containing over five-thousand first names, 
     * begin by sorting it into alphabetical order. Then working out the 
     * alphabetical value for each name, multiply this value by its alphabetical 
     * position in the list to obtain a name score.
     *
     * For example, when the list is sorted into alphabetical order, COLIN, which 
     * is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN
     * would obtain a score of 938 × 53 = 49714.
     *
     * What is the total of all the name scores in the file?
     */
    void Problem22::Solve()
    {
        // The file is a single line containing names CSV-style:
        // "NAME1","NAME2",...,"NAMEX"
        std::string strFilename = "../Data/Euler/p022_names.txt";
        std::vector<std::string> vLines;

        if (!EulerLib::ReadFile(strFilename, vLines))
        {
            return;
        }

        // Read each name from lines
        std::vector<std::string> vNames;

        EulerLib::Tokenize(vLines[0], vNames, ',');
        size_t namesSize = vNames.size();

        // This is necessary to have the real alphabetical position
        std::sort(vNames.begin(), vNames.end());

        // Compute score
        const uint8_t kLetterAOffset = 65;
        uint64_t result = 0;

        for(size_t i = 0; i < namesSize; ++i)
        {
            size_t nameSize = vNames[i].size();
            uint64_t score = 0;

            // Adjust letter offset and exclude surrouding '"'s
            for(size_t s = 1; s < nameSize - 1; ++s)
            {
                score += vNames[i][s] - kLetterAOffset + 1;
            }

            // Adjust by alphabetical position
            result += (score * (i + 1));
        }    

        SetAnswer(result);
    }

}

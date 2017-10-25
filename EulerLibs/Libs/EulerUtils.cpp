#include "EulerUtils.h"

namespace EulerLib {

    /**
     * Open a file and read all line into a vector.
     *
     * @param a_rstrFilename The file name.
     * @param a_rvLines      A vector object to contain lines read.
     *
     * @return Successfully read the file or not.
     */
    bool ReadFile(std::string& a_rstrFilename, std::vector<std::string>& a_rvLines)
    {
        std::ifstream fInputFile;
        std::string   strLine;

        fInputFile.open(a_rstrFilename);

        if (!fInputFile.is_open())
        {
            std::cerr << "[ERROR] Cannot open file." << std::endl;
            return false;
        }

        while (std::getline(fInputFile, strLine))
        {
            a_rvLines.push_back(strLine);
        }

        fInputFile.close();

        return true;
    }

    /**
     * Tokenize a string (as a line)
     *
     * @param a_rstrLine  A string as a line.
     * @param a_rvTokens  Tokens generated.
     * @param a_Delimiter Token separator.
     */
    void Tokenize(std::string& a_rstrLine,
                  std::vector<std::string>& a_rvTokens,
                  char a_Delimiter)
    {
        std::istringstream tokens(a_rstrLine);
        std::string token;

        while(std::getline(tokens, token, ','))
        {
            a_rvTokens.push_back(token);
        }
    }
}
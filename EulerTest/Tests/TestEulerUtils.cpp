#include "TestEulerUtils.h"
#include "Libs/EulerUtils.h"

namespace EulerTest {

    using namespace EulerLib;

    /**
     * Run tests.
     */
    bool TestEulerUtils::Run()
    {
        TestReadFile();
        TestTokenize();
        TestToNumber();
        TestToVector();

        return true;
    }

    /**
     * Test reading a file.
     */
    void TestEulerUtils::TestReadFile()
    {
        std::cout << __FUNCTION__;

        std::string strFilename = "../Data/Test/EulerUtils.txt";
        std::vector<std::string> vLines;

        assert(ReadFile(strFilename, vLines) && "Cannot read file.");

        assert(vLines.size() == 3 && "File should have 3 lines only.");
        assert(vLines[0] == "123" && "First line value is wrong.");
        assert(vLines[1] == "456" && "Second line value is wrong.");
        assert(vLines[2] == "789" && "Third line value is wrong.");

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test tokenize.
     */
    void TestEulerUtils::TestTokenize()
    {
        std::cout << __FUNCTION__;

        std::string strLine = "hello,world,!";
        std::vector<std::string> tokens;

        Tokenize(strLine, tokens, ',');

        assert(tokens.size() == 3 && "Only three tokens.");
        assert(tokens[0] == "hello" && "Wrong token.");
        assert(tokens[1] == "world" && "Wrong token.");
        assert(tokens[2] == "!" && "Wrong token.");

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test number conversion.
     */
    void TestEulerUtils::TestToNumber()
    {
        std::cout << __FUNCTION__;

        std::vector<uint32_t> vDigits;
        uint32_t dwNumber = 0;

        // Test 123456
        vDigits.push_back(1);
        vDigits.push_back(2);
        vDigits.push_back(3);
        vDigits.push_back(4);
        vDigits.push_back(5);
        vDigits.push_back(6);

        dwNumber = ToNumber<uint32_t>(vDigits);

        assert(dwNumber == 123456 &&
               "Number is wrong");

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test vector conversion.
     */
    void TestEulerUtils::TestToVector()
    {
        std::cout << __FUNCTION__;

        std::vector<uint32_t> vDigits;
        uint32_t dwNumber = 1234567;

        ToVector(dwNumber, vDigits);

        for (std::size_t i = 0; i < vDigits.size(); ++i)
        {
            assert(vDigits[i] == (7 - i) &&
                   "Wrong vector conversion.");
        }

        std::cout << "... PASS" << std::endl;
    }
}
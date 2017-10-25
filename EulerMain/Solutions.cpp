#include "Solutions.h"
#include "Answers.h"
#include "Libs/Timer.h"

/**
 * Default constructor.
 */
Solutions::Solutions() :
    m_AppName("Euler"),
    m_bBatchMode(false),
    m_Number(0),
    m_pvProblemList()
{
    Initialize();
}

/**
 * Parse command line arguments.
 *
 * @param a_rCmdLine Command line arguments.
 */
bool Solutions::ParseArgs(TCmdLine& a_rCmdLine)
{
    // Check for actual arguments to parse
    if (a_rCmdLine.size() > 1)
    {
        // Remove executable name
        a_rCmdLine.pop_front();

        while (!a_rCmdLine.empty())
        {
            std::string option(a_rCmdLine.front());
            a_rCmdLine.pop_front();

            if (option == "-h" || option == "--help")
            {
                return DisplayHelp();
            }

            if (option == "-b" || option == "--batch")
            {
                m_bBatchMode = true;
            }
            else if (option == "-l" || option == "--list")
            {
                return DisplayProblemNumbers();
            }
            else
            {
                m_Number = ::atoi(option.c_str());
            }
        }

        if (m_Number > m_pvProblemList.size())
        {
            std::cerr << "[ERROR] Problem number " << m_Number
                        << " does not exist!" << std::endl;
            return false;
        }
        if (!m_bBatchMode && m_Number == 0)
        {
            std::cerr << "[ERROR] You must supply a valid problem number. "
                        << "Try --help." << std::endl;
            return false;
        }
        if (m_bBatchMode && m_Number == 0)
        {
            ++m_Number;
        }

        return true;
    }

    std::cerr << "[ERROR] You must supply a problem number. "
                << "Try --help." << std::endl;

    return false;
}

/**
 * Run a problem to solve.
 *
 * @param a_Number Problem number.
 */
void Solutions::Run()
{

    uint32_t index = m_Number - 1;

    if (m_bBatchMode)
    {
        for (uint32_t i = index; i < m_pvProblemList.size(); ++i)
        {
            m_pvProblemList[i]->Solve();

            CompareAnswers(m_pvProblemList[i]->GetAnswer(), kAnswers[i]);
        }
    }
    else
    {
        EulerLib::Timer  timer;

        timer.Start();
        m_pvProblemList[index]->Solve();
        timer.Stop();

        std::cout << "[INFO] Execution time: " << timer << std::endl;

        CompareAnswers(m_pvProblemList[index]->GetAnswer(), kAnswers[index]);
    }
}

/**
 * Compare answers
 *
 * @param a_rExpected The ex
 */
void Solutions::CompareAnswers(const std::string& a_rSolved, const std::string& a_rExpected) const
{
    if (a_rSolved != "" && a_rSolved != a_rExpected)
    {
        std::cout << "[ERROR] Solved [" << a_rSolved << "] "
                  << "but should be ["  << a_rExpected << "]" << std::endl;
    }
}

/**
 * Display help text.
 *
 * @return Always false to prevent further execution.
 */
bool Solutions::DisplayHelp()
{
    std::cout << "Usage: " << m_AppName << " [OPTIONS] NUMBER" << std::endl;
    std::cout << std::endl;

    std::cout << "  NUMBER                  "
                << "Euler problem number to run." << std::endl;
    std::cout << std::endl;

    std::cout << "  -b, --batch             "
                << "Batch mode to run all problems." << std::endl;
    std::cout << "  -l, --list              "
                << "List solved problems." << std::endl;
    std::cout << std::endl;

    return false;
}
/**
 * Display problem numbers.
 *
 * @return Always false to prevent further execution.
 */
bool Solutions::DisplayProblemNumbers()
{
    std::cout << "Problems solved so far: [1, " << m_pvProblemList.size() << "]" << std::endl;

    return false;
}
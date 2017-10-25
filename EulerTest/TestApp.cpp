#include "TestApp.h"
#include "Libs/Timer.h"

/**
 * Default constructor.
 */
TestApp::TestApp() :
    m_AppName("Test"),
    m_TestName("all"),
    m_eTestType(E_UNITTEST)
{
    Initialize();
}

/**
 * Destructor.
 */
TestApp::~TestApp()
{
    TestDict::iterator unitIt = m_pUnitTestLookup.begin();

    for (; unitIt != m_pUnitTestLookup.end(); ++unitIt)
    {
        delete unitIt->second;
    }
    m_pUnitTestLookup.clear();

    TestDict::iterator perfIt = m_pPerfTestLookup.begin();

    for (; perfIt != m_pPerfTestLookup.end(); ++perfIt)
    {
        delete perfIt->second;
    }
    m_pPerfTestLookup.clear();
}

/**
 * Parse application command line arguments
 *
 * @param a_rCmdLine Reference to command line arguments.
 *
 * @return Decoding of options status.
 */
bool TestApp::ParseArgs(TCmdLine& a_rCmdLine)
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

            if (option == "-t" || option == "--test")
            {
                if (a_rCmdLine.empty())
                {
                    std::cerr << "[ERROR] Option -t/--test must have an argument. "
                        << "Try --help" << std::endl;
                    return false;
                }

                std::string value(a_rCmdLine.front());
                a_rCmdLine.pop_front();

                if (value == "PERF")
                {
                    m_eTestType = E_PERFTEST;
                }
                else if (value == "UNIT")
                {
                    m_eTestType = E_UNITTEST;
                }
                else
                {
                    m_eTestType = E_NULLTEST;
                }
            }
            else if (option == "-n" || option == "--name")
            {
                if (a_rCmdLine.empty())
                {
                    std::cerr << "[ERROR] Option -n/--name must have an argument. "
                        << "Try --help" << std::endl;
                    return false;
                }

                m_TestName = std::string(a_rCmdLine.front());
                a_rCmdLine.pop_front();
            }
            else if (option == "-l" || option == "--list")
            {
                return DisplayTestName();
            }
        }
    }

    return SanitityCheckArgs();
}

/**
 * Verify parsed arguments are valid.
 *
 * @return Whether all arguments are valid or not.
 */
bool TestApp::SanitityCheckArgs()
{
    // Verify options for illegal values or combinations
    if (m_eTestType == E_NULLTEST)
    {
        std::cerr << "[ERROR] Unrecognized argument for -t/--test. "
                    << "Try --help" << std::endl;
        return false;
    }
    if (m_eTestType == E_PERFTEST)
    {
        if (m_TestName == "all")
        {
            std::cerr << "[ERROR] Performance test must be called with a name. "
                        << "Try --help" << std::endl;
            return false;
        }
        if (m_pPerfTestLookup.find(m_TestName) == m_pPerfTestLookup.end())
        {
            std::cerr << "[ERROR] No such test." << std::endl;
            return false;
        }
    }
    else if (m_eTestType == E_UNITTEST && m_TestName != "all")
    {
        if (m_pUnitTestLookup.find(m_TestName) == m_pUnitTestLookup.end())
        {
            std::cerr << "[ERROR] No such test." << std::endl;
            return false;
        }
    }

    return true;
}

/**
 * Run tests
 *
 * @return Run status.
 */
bool TestApp::Run()
{
    // Run tests based on test types
    if (m_eTestType == E_PERFTEST)
    {
        // Call the performance test required
        std::cout << "[INFO] Running test: " << m_TestName << std::endl;
        m_pPerfTestLookup[m_TestName]->Run();
    }
    else
    {
        // Setup a timer to time the execute of the unit tests.
        EulerLib::Timer timer;

        timer.Start();

        // Run unit test(s).
        if (m_TestName == "all")
        {
            TestDict::const_iterator unitIt = m_pUnitTestLookup.begin();

            for (; unitIt != m_pUnitTestLookup.end(); ++unitIt)
            {
                unitIt->second->Run();
            }
        }
        else
        {
            std::cout << "[INFO] Running test: " << m_TestName << std::endl;
            m_pUnitTestLookup[m_TestName]->Run();
        }

        timer.Stop();
        std::cout << "[INFO] Execution time: " << timer << std::endl;
    }

    return true;
}

/**
 * Initialize all tests.
 */
void TestApp::Initialize()
{
    // Initialize unit tests.
    InitializeUnitTest(new EulerTest::TestEulerUtils());
    InitializeUnitTest(new EulerTest::TestEulerMath());
    InitializeUnitTest(new EulerTest::TestBigInteger());
    InitializeUnitTest(new EulerTest::TestModularArith());
    InitializeUnitTest(new EulerTest::TestLexicographicPermutation());
    InitializeUnitTest(new EulerTest::TestDivisorFunction());
    InitializeUnitTest(new EulerTest::TestPrimeCounter());
    InitializeUnitTest(new EulerTest::TestEratosthenesSieve());
    InitializeUnitTest(new EulerTest::TestPrimeFactorizer());
    InitializeUnitTest(new EulerTest::TestFibonacciSequence());

    // Initialize performance tests.
    InitializePerfTest(new EulerTest::PerfPrimeFactorizer());
}

/**
 * Initialize a unit test case.
 *
 * @param a_pTestCase Test case to initialize.
 */
void TestApp::InitializeUnitTest(TestCase * a_pTestCase)
{
    m_pUnitTestLookup[a_pTestCase->GetTestName()] = a_pTestCase;
}

/**
 * Initialize a performance test case.
 *
 * @param a_pTestCase Test case to initialize.
 */
void TestApp::InitializePerfTest(TestCase * a_pTestCase)
{
    m_pPerfTestLookup[a_pTestCase->GetTestName()] = a_pTestCase;
}

/**
 * Display help text.
 *
 * @return Always false to prevent further execution.
 */
bool TestApp::DisplayHelp()
{
    std::cout << "Usage: " << m_AppName << " [OPTIONS]" << std::endl;
    std::cout << std::endl;

    std::cout << "Running tests:" << std::endl;
    std::cout << "  -t, --test TYPE         "
                << "Specify test type: UNIT or PERF." << std::endl;
    std::cout << "  -n, --name NAME         "
                << "Specify a test name to run. It is mandatory for PERF only." << std::endl;
    std::cout << "                          "
                << "If not specified for UNIT, keyword `all' is used." << std::endl;
    std::cout << "  -l, --list              "
                << "List all tests." << std::endl;
    std::cout << std::endl;

    std::cout << "Miscellaneous:" << std::endl;
    std::cout << "  -h, --help              "
                << "Display help text and exit." << std::endl;
    std::cout << std::endl;

    return false;
}

/**
 * Display a list of all tests name.
 *
 * @return Always false to prevent further execution.
 */
bool TestApp::DisplayTestName()
{
    std::cout << "Unit tests: " << std::endl;

    TestDict::const_iterator unitIt = m_pUnitTestLookup.begin();

    for (; unitIt != m_pUnitTestLookup.end(); ++unitIt)
    {
        std::cout << "  - " << unitIt->second->GetTestName() << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Performance tests: " << std::endl;

    TestDict::const_iterator perfIt = m_pPerfTestLookup.begin();

    for (; perfIt != m_pPerfTestLookup.end(); ++perfIt)
    {
        std::cout << "  - " << perfIt->second->GetTestName() << std::endl;
    }

    return false;
}

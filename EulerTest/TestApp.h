#ifndef __EULER_TESTAPP__
#define __EULER_TESTAPP__

#include "EulerTest.h"

/**
 * This is the main test application.
 */
class TestApp {

public:
    /**
     * Type of tests supported.
     */
    enum ETestType { E_NULLTEST, E_UNITTEST, E_PERFTEST };

    /**
     * Command line arguments definition.
     */
    typedef std::list<char *> TCmdLine;

    TestApp();
    ~TestApp();

    bool ParseArgs(TCmdLine& a_rCmdLine);
    bool Run();

private:
	typedef std::map<std::string, TestCase *> TestDict;

    void Initialize();
    void InitializeUnitTest(TestCase * a_pTestCase);
    void InitializePerfTest(TestCase * a_pTestCase);

	bool SanitityCheckArgs();

    bool DisplayHelp();
    bool DisplayTestName();

    std::string m_AppName;
    std::string m_TestName;
    ETestType   m_eTestType;

    //std::vector<TestCase *> m_pUnitTests;
    std::vector<TestCase *> m_pPerfTests;
	TestDict m_pUnitTestLookup;
	TestDict m_pPerfTestLookup;
};

#endif // __EULER_TESTAPP__
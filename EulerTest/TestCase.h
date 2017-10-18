#ifndef __EULER_TESTCASE_H__
#define __EULER_TESTCASE_H__

/**
 * Class TestCase:
 *
 * It is an interface class for any test.
 */
class TestCase {

public:
    virtual ~TestCase()
    {}

    const std::string& GetTestName() { return m_TestName; };

    virtual bool Run() = 0;

protected:
    TestCase(const char * a_ptestName) : m_TestName(a_ptestName)
    {}
    
    std::string m_TestName;
};

#endif // __EULER_TESTCASE_H__
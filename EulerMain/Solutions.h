#ifndef __SOLUTIONS_H__
#define __SOLUTIONS_H__

#include <list>
#include "Problem.h"

class Solutions {

public:
    typedef std::list<char *> TCmdLine;

public:
    Solutions();

    bool ParseArgs(TCmdLine& a_rCmdLine);
    void Run();

private:
    void Initialize();
    void CompareAnswers(const std::string& a_rSolved, const std::string& a_rExpected) const;

    bool DisplayHelp();
    bool DisplayProblemNumbers();

    std::string m_AppName;
    bool        m_bBatchMode;
    uint32_t    m_Number;

    std::vector<Euler::Problem *> m_pvProblemList;
};


#endif // __SOLUTIONS_H__
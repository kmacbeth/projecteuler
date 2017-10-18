#ifndef __EULER_PROBLEM_H__
#define __EULER_PROBLEM_H__

#include "Libs\Euler.h"

namespace Euler {

    class Problem {

    public:
        virtual ~Problem() {}

        const std::string& GetProblemName() { return m_ProblemName; }
        const std::string& GetAnswer()      { return m_Answer; }
        
        template<class T> inline void SetAnswer(T& a_rAnswer);
        template<>        inline void SetAnswer(std::string& a_rstrAnswer);
        
        virtual void Solve() = 0;

    protected:
        Problem(const char * a_pProblemName) : 
            m_ProblemName(a_pProblemName),
            m_Answer("")
        {}

        inline void ShowAnswer() 
        { 
            std::cout << m_ProblemName << ": " << m_Answer << std::endl;
        }

        std::string m_ProblemName;
        std::string m_Answer;
    };

    /**
     * Template function to set an answer.
     *
     * @param a_rAnswer Reference to an answer.
     */
    template<class T>
    inline void Problem::SetAnswer(T& a_rAnswer)
    { 
        m_Answer = std::to_string(a_rAnswer);
        ShowAnswer();
    }

    /**
     * Specialiazed template function for std::string
     *
     * @param a_rstrAnswer Reference to answer std::string.
     */
    template<>
    inline void Problem::SetAnswer(std::string& a_rstrAnswer)
    { 
        m_Answer = a_rstrAnswer; 
        ShowAnswer();
    }

}

#endif // __EULER_PROBLEM_H__
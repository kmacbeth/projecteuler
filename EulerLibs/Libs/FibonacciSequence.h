#ifndef __EULER_FIBONACCISEQUENCE_H__
#define __EULER_FIBONACCISEQUENCE_H__

#include "Euler.h"

namespace EulerLib {

    template<typename T>
    class FibonacciSequence {
        
    public:
        FibonacciSequence(T a_First, T a_Second);

        T operator()();

    private:
        T m_First;
        T m_Second;
    };

    /**
     * Constructor.
     *
     * To start a Fibonacci sequence, we put set initial conditions.
     *
     * @param a_First First number.
     * @param a_Second Second number.
     *
     * @note We can start a fibonacci sequence with two valid fibonacci
     *       numbers such as (0, 1), (1, 1), (1, 2), etc.
     */
    template<typename T>
    FibonacciSequence<T>::FibonacciSequence(T a_First, T a_Second) :
        m_First(a_First),
        m_Second(a_Second)
    {
    }

    /**
     * Return the next fibonacci number.
     *
     * @return Next fibonacci number.
     */
    template<typename T>
    T FibonacciSequence<T>::operator()()
    {
        T sum = m_First + m_Second;

        m_First = m_Second;
        m_Second = sum;

        return sum;
    }

}

#endif // __EULER_FIBONACCISEQUENCE_H__
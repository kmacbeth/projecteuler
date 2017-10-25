#ifndef __EULER_TIMER_H__
#define __EULER_TIMER_H__

#include <chrono>
#include "Euler.h"

namespace EulerLib {

    class Timer {

    public:

        void Start() { m_Start = std::chrono::high_resolution_clock::now(); }
        void Stop()  { m_End   = std::chrono::high_resolution_clock::now(); }

        double GetDeltaTime() { return TimeElapsed().count(); }

        friend std::ostream& operator<< (std::ostream& stream, const Timer& timer)
        {
            return stream << timer.TimeElapsed().count() << "s";
        }


    private:

        // VS2012: resolution is only MS
        std::chrono::duration<double> TimeElapsed() const
        {
            std::chrono::duration<double, std::micro> elapsed = m_End - m_Start;
            return elapsed;
        }

        std::chrono::high_resolution_clock::time_point m_Start;
        std::chrono::high_resolution_clock::time_point m_End;
    };

}

#endif // __EULER_TIMER_H__
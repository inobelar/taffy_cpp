#include "platform_timer.h"

/**********************************************************************
    class: PlatformTimer (platform_timer_win.cpp)

    author: S. Hau
    date: September 28, 2017

    Windows implementation for precise time measurement.
    Because the platform dependant time measurement is generally more
    precise, it is wise to implement it for every platform.
**********************************************************************/

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace OS {

    //----------------------------------------------------------------------
    void PlatformTimer::_Init()
    {
        LARGE_INTEGER frequency;
        QueryPerformanceFrequency( &frequency );

        m_tickFrequency = frequency.QuadPart;
        m_tickFrequencyInSeconds = 1.0 / m_tickFrequency;
    }

    //----------------------------------------------------------------------
    uint64_t PlatformTimer::getTicks()
    {
        LARGE_INTEGER ticks;
        QueryPerformanceCounter( &ticks );

        return uint64_t( ticks.QuadPart );
    }

    //----------------------------------------------------------------------
    SystemTime PlatformTimer::getCurrentTime()
    {
        SYSTEMTIME systemTime;
        GetLocalTime( &systemTime );

        SystemTime st;
        st.year         = systemTime.wYear;
        st.month        = systemTime.wMonth;
        st.dayOfWeek    = systemTime.wDayOfWeek;
        st.day          = systemTime.wDay;
        st.hour         = systemTime.wHour;
        st.minute       = systemTime.wMinute;
        st.second       = systemTime.wSecond;
        st.milliseconds = systemTime.wMilliseconds;

        return st;
    }

} // end namespaces

#endif // _WIN32

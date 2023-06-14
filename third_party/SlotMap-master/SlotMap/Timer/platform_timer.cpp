#include "platform_timer.h"

/**********************************************************************
    class: PlatformTimer (platform_timer.cpp)

    author: S. Hau
    date: October 12, 2017

**********************************************************************/

namespace OS {

    //----------------------------------------------------------------------
    PlatformTimer   PlatformTimer::m_instance;
    uint64_t        PlatformTimer::m_tickFrequency = 0;
    double          PlatformTimer::m_tickFrequencyInSeconds = 0;

}
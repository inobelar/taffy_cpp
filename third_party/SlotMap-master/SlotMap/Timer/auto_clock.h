#pragma once

#include "platform_timer.h"

#include <stdio.h>

class AutoClock
{
    uint64_t m_startTicks;
public:
    AutoClock()
    {
        m_startTicks = OS::PlatformTimer::getTicks();
    }

    ~AutoClock()
    {
        uint64_t dur = OS::PlatformTimer::getTicks() - m_startTicks;
        double durInTime = OS::PlatformTimer::ticksToSeconds(dur);
        printf_s("<<< %fs has passed >>>\n", durInTime);
    }
};
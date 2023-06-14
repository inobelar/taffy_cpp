#pragma once

/**********************************************************************
    class: PlatformTimer (platform_timer.h)

    author: S. Hau
    date: September 28, 2017

    Specifies the interface for platform independant time queries.
    Access via static methods.
**********************************************************************/

#include "system_time.hpp"
#include <cstdint>

namespace OS {

    class PlatformTimer
    {
        // Private constructor. Only one static instance allowed for initialization.
        PlatformTimer() { _Init(); } 

    public:
        //----------------------------------------------------------------------
        // Returns the current time of the pc.
        // @Return: 
        //   Struct which contains the time like year, month, day etc.
        //----------------------------------------------------------------------
        static SystemTime getCurrentTime();

        //----------------------------------------------------------------------
        // Returns the number of ticks since the pc was started.
        // Query how much a tick is in time with getTickFrequencyInSeconds()
        // @Return: 
        //   Amount of ticks since the pc was started.
        //----------------------------------------------------------------------
        static uint64_t getTicks();

        //----------------------------------------------------------------------
        // Returns the frequency of the used clock.
        // (1.0 / frequency) delievers the interval in seconds.
        //----------------------------------------------------------------------
        static inline uint64_t getTickFrequency() { return m_tickFrequency; }

        //----------------------------------------------------------------------
        // Returns the frequency of the used clock in seconds.
        // Multiply the amount of ticks with this to get the final passed
        // time in seconds or use the function ticksToSeconds(...).
        //----------------------------------------------------------------------
        static inline double getTickFrequencyInSeconds() { return m_tickFrequencyInSeconds; }

        //----------------------------------------------------------------------
        // Converts amount of ticks to passed time in different formats.
        //----------------------------------------------------------------------
        static inline double ticksToSeconds(uint64_t ticks) { return ticks * getTickFrequencyInSeconds(); }
        static inline double ticksToMilliSeconds(uint64_t ticks) { return ticksToSeconds(ticks) * 1000.0; }
        static inline double ticksToMicroSeconds(uint64_t ticks) { return ticksToMilliSeconds(ticks) * 1000.0; }
        static inline double ticksToNanoSeconds(uint64_t ticks) { return ticksToMicroSeconds(ticks) * 1000.0; }

    private:
        static PlatformTimer    m_instance;
        static uint64_t              m_tickFrequency;
        static double              m_tickFrequencyInSeconds;

        void _Init();

        // Forbid copy + copy assignment and rvalue copying
        PlatformTimer (const PlatformTimer& other)              = delete;
        PlatformTimer& operator= (const PlatformTimer& other)   = delete;
        PlatformTimer (PlatformTimer&& other)                   = delete;
        PlatformTimer& operator= (PlatformTimer&& other)        = delete;
    };

}
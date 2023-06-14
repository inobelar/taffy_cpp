#pragma once

/**********************************************************************
    class: SystemTime (system_time.hpp)

    author: S. Hau
    date: September 28, 2017

    Contains a POD struct "SystemTime" used to represent precise
    time points.
**********************************************************************/

#include <cstdint>

//----------------------------------------------------------------------
// Defines
//----------------------------------------------------------------------

#define SECOND_IN_MILLIS   1000i64
#define MINUTE_IN_MILLIS   SECOND_IN_MILLIS * 60i64
#define HOUR_IN_MILLIS     MINUTE_IN_MILLIS * 60i64
#define DAY_IN_MILLIS      HOUR_IN_MILLIS   * 24i64
#define MONTH_IN_MILLIS    DAY_IN_MILLIS    * 30i64
#define YEAR_IN_MILLIS     MONTH_IN_MILLIS  * 12i64

namespace OS {

    //----------------------------------------------------------------------
    // POD SystemTime
    //----------------------------------------------------------------------

    struct SystemTime
    {
        int year;               // years since 0000 - [0 - infinity]
        int month;              // months since January - [1, 12]
        int dayOfWeek;          // days since Sunday - [0, 6]
        int day;                // day of the month - [1, 31]
        int hour;               // hours since midnight - [0, 23]
        int minute;             // minutes after the hour - [0, 59]
        int second;             // seconds after the minute - [0, 59] 
        int milliseconds;       // milliseconds - [0, 999]

        SystemTime() 
            : year(0), month(0), dayOfWeek(0), day(0), hour(0), minute(0), second(0), milliseconds(0) 
        {}

        // Convert the systemtime to milliseconds since Jan 1st, 1970.
        // It's not 100% precise because it is assumed every month has 30 days.
        uint64_t timeSinceEpoche() const
        {
            return milliseconds +
                   second * SECOND_IN_MILLIS +
                   minute * MINUTE_IN_MILLIS +
                   hour * HOUR_IN_MILLIS +
                   day * DAY_IN_MILLIS +
                   month * MONTH_IN_MILLIS +
                   (year - 1970) * YEAR_IN_MILLIS;
        }

        // Check if two system times are identical.
        bool equals(const SystemTime& other) const
        {
            return milliseconds == other.milliseconds && 
                   second == other.second && 
                   minute == other.minute && 
                   hour == other.hour && 
                   day == other.day && 
                   dayOfWeek == other.dayOfWeek &&
                   month == other.month && 
                   year == other.year;
        }

        bool operator == (const SystemTime& other) const { return (*this).equals(other); }
        bool operator != (const SystemTime& other) const { return !(*this).equals(other); }
        bool operator < (const SystemTime& other) const { return timeSinceEpoche() < other.timeSinceEpoche(); }
        bool operator > (const SystemTime& other) const { return timeSinceEpoche() > other.timeSinceEpoche(); }
    };

}

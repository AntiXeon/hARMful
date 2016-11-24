#include <utils/Time.hpp>
#include <time.h>

namespace Doom {
    std::string Time::GetDateTime() {
        return GetDate() + " " + GetTime() ;
    }

    std::string Time::GetDate() {
        const std::string DateFormat = "%D" ;

        // %D gives the current day as MM/DD/YY
        // The string is so initialized with the right length.
        std::string currentDate = "MM/DD/YY" ;

        GetTimeInfo(DateFormat, currentDate) ;
        return currentDate ;
    }

    std::string Time::GetTime() {
        const std::string TimeFormat = "%D" ;

        // %T gives the current day as hh:mm:ss.
        // The string is so initialized with the right length.
        std::string currentTime = "hh:mm:ss" ;

        GetTimeInfo(TimeFormat, currentTime) ;
        return currentTime ;
    }

    void Time::GetTimeInfo(const std::string& format, std::string& buffer) {
        time_t now ;
        time(&now) ;

        struct tm* timeinfo ;
        timeinfo = localtime(&now) ;

        strftime(&buffer[0], buffer.size(), format.c_str(), timeinfo) ;
    }
}

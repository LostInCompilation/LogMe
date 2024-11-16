/*
    The zlib License

    Copyright (C) 2024 Marc Schöndorf
 
This software is provided 'as-is', without any express or implied warranty. In
no event will the authors be held liable for any damages arising from the use of
this software.

Permission is granted to anyone to use this software for any purpose, including
commercial applications, and to alter it and redistribute it freely, subject to
the following restrictions:

1.  The origin of this software must not be misrepresented; you must not claim
    that you wrote the original software. If you use this software in a product,
    an acknowledgment in the product documentation would be appreciated but is
    not required.

2.  Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

3.  This notice may not be removed or altered from any source distribution.
*/

/*------------------------------------------------------------------*/
/*                                                                  */
/*                          LOG ME LIBRARY                          */
/*                                                                  */
/*                      (C) 2024 Marc Schöndorf                     */
/*                            See license                           */
/*                                                                  */
/*  Clock.hpp                                                       */
/*  Created: 14.11.2024                                             */
/*------------------------------------------------------------------*/

namespace LogMe
{
class Clock final
{
private:
    using HighResClock = std::chrono::high_resolution_clock;
    
    using Rep = std::chrono::high_resolution_clock::duration::rep;
    using Period = std::chrono::high_resolution_clock::duration::period;
    
public:
    Clock() = delete;
    
    static std::chrono::time_point<HighResClock> Now()          { return HighResClock::now(); }
    static std::chrono::duration<Rep, Period> TimeSinceEpoch()  { return Now().time_since_epoch(); }
    
    static std::uintmax_t GetNanoSeconds()  { return std::chrono::duration_cast<std::chrono::nanoseconds>(TimeSinceEpoch()).count(); }
    static std::uintmax_t GetMicroSeconds() { return std::chrono::duration_cast<std::chrono::microseconds>(TimeSinceEpoch()).count(); }
    static std::uintmax_t GetMilliSeconds() { return std::chrono::duration_cast<std::chrono::milliseconds>(TimeSinceEpoch()).count(); }
    static std::uintmax_t GetSeconds()      { return std::chrono::duration_cast<std::chrono::seconds>(TimeSinceEpoch()).count(); }
};
}

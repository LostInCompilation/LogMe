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
/*                      LOG ME LIBRARY TESTING                      */
/*                                                                  */
/*                      (C) 2024 Marc Schöndorf                     */
/*                            See license                           */
/*                                                                  */
/*  Main.hpp                                                        */
/*  Created: 28.10.2024                                             */
/*------------------------------------------------------------------*/

#include <iostream>

#include "LogMe.hpp"
#include "CLI11.hpp"

const std::string VERSION_STRING = "Version 0.1";

int ParseCommandLine(const int argc, char** argv)
{
    CLI::App cliApp("Description", "LogMe_testing");
    
    // For Unicode support on all platforms
    char** const unicode_argv = cliApp.ensure_utf8(argv);
    
    // *******************************************************
    // Settings
    cliApp.footer("Footer");
    cliApp.get_formatter()->label("TEXT", "STRING");
#ifdef PLATFORM_WINDOWS
    cliApp->allow_windows_style_options();
#endif
    
    // *******************************************************
    // Command line options
    //cliApp.add_option("-p,--path", startPathStr, "Path to start scanning in");
    //cliApp.add_flag("-a,--all", m_CLIShowAllFiles, "Show hidden files");//->group("SETTINGS");
    
    // *******************************************************
    // Special flags
    cliApp.set_version_flag("-v,--version", VERSION_STRING)->group("INFO");
    cliApp.set_help_flag("-h,--help", "Display help and exit")->group("INFO");
    
    // *******************************************************
    // Parse
    try {
        cliApp.parse(argc, unicode_argv);
    }
    catch (const CLI::ParseError& e) {
        return cliApp.exit(e);
    }
    
    return -1;
}

int main(int argc, char** argv)
{
    // Parse command line
    const int parseReturn = ParseCommandLine(argc, argv);
    if(parseReturn >= 0) // Error or special CLI flag?
        return parseReturn;

    std::cout << "LogMe Testing Executable" << std::endl;
    std::cout << "=============================================================" << std::endl << std::endl;
    
    std::cout << "HighRes clock is steady: " << std::boolalpha << std::chrono::high_resolution_clock::is_steady << std::endl;
    std::cout << "HighRes clock ns: " << LogMe::Clock<>::GetNanoSeconds() << std::endl;
    std::cout << "HighRes clock s: " << LogMe::Clock<>::GetSeconds() << std::endl;
    std::cout << "Time: " << std::format("{:%Y/%m/%d %H:%M:%S}", LogMe::Clock<LogMe::SystemClock>::Now()) << std::endl;
    
    //auto const time = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
    
    return 0;
}

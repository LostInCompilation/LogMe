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
/*  Platform.hpp                                                    */
/*  Created: 14.11.2024                                             */
/*------------------------------------------------------------------*/

/*------------------------------------------------------------------*/
/*                             Settings                             */
/*------------------------------------------------------------------*/
// Dummy

/*------------------------------------------------------------------*/
/*                         Internal checks                          */
/*                                                                  */
/*                          DO NOT MODIFY                           */
/*------------------------------------------------------------------*/
#ifndef __cpp_lib_chrono // Check for chrono lib support
#error Chrono library is not supported by this compiler or C++ standard.
#endif

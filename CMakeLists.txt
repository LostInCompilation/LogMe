################################################################################
#                        CMake file for LogMe Library.                         #
#                                                                              #
# (C) 2024 Marc Schöndorf                                                      #
# Licensed under the zlib License. See LICENSE.md                              #
################################################################################

cmake_minimum_required(VERSION 3.25)

###########################################################
# Helper for formatting and printing text with color
include("cmake additional/colorFormatting.cmake")

###########################################################
# Set options for sub projects
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW) # Needed to set options of subprojects inside parent project

###########################################################
# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_EXTENSIONS false) # Don't use GNU++

###########################################################
# Set options for libs
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW) # Needed to set options from subprojects in parent project

###########################################################
# Set build output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/release")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/debug")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/debug")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/release")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/debug")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/debug")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/release")

###########################################################
# Our project
project("LogMe"
	VERSION 0.1.0
	DESCRIPTION "Fast asynchronous C++20 Logging Library."
	LANGUAGES CXX
)

# Main lib
add_library("${PROJECT_NAME}"
    include/LogMe.hpp
	include/LogMeVersion.hpp
	include/Platform.hpp
	include/Clock.hpp
	src/LogMe.cpp
)

# The projects include directories
target_include_directories("${PROJECT_NAME}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

###########################################################
# Project versioning
configure_file("cmake additional/LogMeVersion.hpp.cmake" "${CMAKE_CURRENT_SOURCE_DIR}/include/LogMeVersion.hpp")

###########################################################
# macOS frameworks
#if (APPLE)
    #target_link_libraries("${PROJECT_NAME}" PRIVATE "-framework CoreFoundation")
#endif()

###########################################################
# Linux frameworks
#if (UNIX AND NOT APPLE)
#	find_package(PkgConfig REQUIRED)
#	pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
#
#    target_include_directories("${PROJECT_NAME}" PRIVATE "${GTK3_INCLUDE_DIRS}")
#    target_link_directories("${PROJECT_NAME}" PRIVATE "${GTK3_LIBRARY_DIRS}")
#    target_link_libraries("${PROJECT_NAME}" PRIVATE "${GTK3_LIBRARIES}")
#    target_compile_options("${PROJECT_NAME}" PRIVATE "${GTK3_CFLAGS_OTHER}")
#endif()

###########################################################
# Include example projects
add_subdirectory("examples/basic example")
add_subdirectory("examples/testing")

###########################################################
# Macro for removing /RTC flag in VisualStudio (incompatible with /O2 optimization)
macro(RemoveRTCFlagDebug_VS)
	string(REGEX REPLACE "/RTC[^ ]*" "" CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG}")
endmacro()

macro(RemoveRTCFlagRelease_VS)
	string(REGEX REPLACE "/RTC[^ ]*" "" CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE}")
endmacro()

#############################################################
# Optimization settings
if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
	if (WIN32 AND MSVC)
		# Visual Studio on Windows
		target_compile_options("${PROJECT_NAME}" PRIVATE "/O2")
		RemoveRTCFlagDebug_VS()
		RemoveRTCFlagRelease_VS()
	else()
		# Assume -O3 for gcc/clang like
		target_compile_options("${PROJECT_NAME}" PRIVATE "-O3")
	endif()
endif()

#############################################################
# Compiler settings (example)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang") # GCC
	if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64") # Do we compile for arm64?
		#target_compile_options("${PROJECT_NAME}" PRIVATE "-march=armv8-a+crypto+crc")
		#target_compile_options("${PROJECT_NAME}" PRIVATE "-ftree-vectorize")
	elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "Win32")
		#target_compile_options("${PROJECT_NAME}" PRIVATE "-march=native")
		#target_compile_options("${PROJECT_NAME}" PRIVATE "-ftree-vectorize")
	endif()
endif()

###########################################################
# Enable a lot of warnings
if (WIN32)
	if (MSVC)
		target_compile_options("${PROJECT_NAME}" PRIVATE "/W3")
		#target_compile_options("${PROJECT_NAME}" PRIVATE "/WX")
		#target_compile_options("${PROJECT_NAME}" PRIVATE "/wd4244")
		#target_compile_options("${PROJECT_NAME}" PRIVATE "/wd4267")
		target_compile_options("${PROJECT_NAME}" PRIVATE "/D_CRT_SECURE_NO_WARNINGS")
	endif()
	# Force Win32 to UNICODE
	target_compile_definitions("${PROJECT_NAME}" PRIVATE UNICODE _UNICODE)
	#target_compile_options("${PROJECT_NAME}" PRIVATE "/utf-8")
else()
	target_compile_options("${PROJECT_NAME}" PRIVATE "-Wall")
	target_compile_options("${PROJECT_NAME}" PRIVATE "-Wextra")
	target_compile_options("${PROJECT_NAME}" PRIVATE "-pedantic")
	target_compile_options("${PROJECT_NAME}" PRIVATE "-Wmissing-declarations")
	target_compile_options("${PROJECT_NAME}" PRIVATE "-Wdeprecated")
	target_compile_options("${PROJECT_NAME}" PRIVATE "-Wshadow")
	target_compile_options("${PROJECT_NAME}" PRIVATE "-Wsign-conversion")
endif()

###########################################################
# Include summary file for printing various information
include("cmake additional/printSummary.cmake")

# Print the information
PRINT_SUMMARY()

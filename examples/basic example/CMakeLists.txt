################################################################################
#                    CMake file for LogMe Library examples.                    #
#                                                                              #
# (C) 2024 Marc Schöndorf                                                      #
# Licensed under the zlib License. See LICENSE.md                              #
################################################################################

cmake_minimum_required(VERSION 3.29)

###########################################################
# Use C++20
# NOTE: Already set in parent project (LogMe lib)
#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED true)
#set(CMAKE_CXX_EXTENSIONS false)

###########################################################
# Our project
project("LogMe_basic_example"
	VERSION 1.0.0
	DESCRIPTION "LogMe Library Basic Example"
	LANGUAGES CXX
)

# Main executable
add_executable("${PROJECT_NAME}"
	Main.cpp
)

###########################################################
# Use LogMe lib
target_link_libraries("${PROJECT_NAME}" PRIVATE LogMe)
target_include_directories("${PROJECT_NAME}" PRIVATE "${CMAKE_SOURCE_DIR}/include")

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

###########################################################
# Add as many warnings as possible
if (WIN32)
	if (MSVC)
		target_compile_options("${PROJECT_NAME}" PRIVATE "/W3")
		target_compile_options("${PROJECT_NAME}" PRIVATE "/WX")
		target_compile_options("${PROJECT_NAME}" PRIVATE "/wd4244")
		target_compile_options("${PROJECT_NAME}" PRIVATE "/wd4267")
		target_compile_options("${PROJECT_NAME}" PRIVATE "/D_CRT_SECURE_NO_WARNINGS")
	endif()
	# Force Win32 to UNICODE
	target_compile_definitions("${PROJECT_NAME}" PRIVATE UNICODE _UNICODE)
else()
	target_compile_options("${PROJECT_NAME}" PRIVATE "-Wall")
	target_compile_options("${PROJECT_NAME}" PRIVATE "-Wextra")
	target_compile_options("${PROJECT_NAME}" PRIVATE "-pedantic")
	target_compile_options("${PROJECT_NAME}" PRIVATE "-Wmissing-declarations")
	target_compile_options("${PROJECT_NAME}" PRIVATE "-Wdeprecated")
	target_compile_options("${PROJECT_NAME}" PRIVATE "-Wshadow")
	#target_compile_options("${PROJECT_NAME}" PRIVATE "-Werror")
	#target_compile_options("${PROJECT_NAME}" PRIVATE "-Wsign-conversion")
endif()

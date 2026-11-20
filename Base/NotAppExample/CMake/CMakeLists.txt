# --------------------------------------------------------------------
# NotAppExample : Not Application Example 
# GEN FrameWork
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.16.0)

# --------------------------------------------------------------------
# PreProject

set(GEN_DIRECTORY "../../../..") 

option(USE_CLANG_COMPILER_FEATURE                               "Use Clang Compiler"                                      ON)
include("${GEN_DIRECTORY}/Common/CMake/GEN_PreProject.cmake")

project(notappexample)

# --------------------------------------------------------------------
# Activate features/Defines

option(DEBUG_FEATURE                                            "Activate Debug mode"                                     ON ) 
option(XTRACE_FEATURE                                           "Activate XTrace"                                         ON )
option(XMEMORY_CONTROL_FEATURE                                  "Activate XMemory Control"                                ON )


option(XSLEEP_FEATURE                                           "Sleep functions"                                         ON )


# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/Common/CMake/GEN_Main.cmake") 
 
 
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Sources")
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/NotAppExample.cpp")


# --------------------------------------------------------------------
# End Proyect 

include("${GEN_DIRECTORY}/Common/CMake/GEN_End.cmake")



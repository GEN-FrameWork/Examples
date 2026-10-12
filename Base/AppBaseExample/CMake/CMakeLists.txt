# --------------------------------------------------------------------
# appbaseexample : minimal base example with APP class
# GEN FrameWork
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.16.0)
project(appbaseexample)


set(GEN_DIRECTORY "../../../..") 


# --------------------------------------------------------------------
# Activate features/Defines

option(DEBUG_FEATURE                                            "Debug mode"                                              ON )
option(XTRACE_FEATURE                                           "XTrace"                                                  ON )
option(XMEMORY_CONTROL_FEATURE                                  "XMemory Control"                                         ON )
option(XFEEDBACK_CONTROL_FEATURE                                "XFeedback Control"                                       ON )     

option(USE_CLANG_COMPILER_FEATURE                               "Use Clang Compiler"                                      ON )
    
option(LINUX_VISUALSTUDIO_CP1252_FEATURE                        "Linux CodePage Editor Visual Studio CP1252"              ON )   
                                
option(APPFLOW_FEATURE                                          "Application Flow modules"                                ON )


# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/Common/CMake/GEN_Main.cmake") 

                     
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Sources")
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/AppBaseExample.cpp")
 

# --------------------------------------------------------------------
# End Proyect 

include("${GEN_DIRECTORY}/Common/CMake/GEN_End.cmake")


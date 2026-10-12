# --------------------------------------------------------------------
# LogLib : Log Library 
# GEN FrameWork
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.16.0)
project(loglib)


set(GEN_DIRECTORY "../../../..") 


# --------------------------------------------------------------------
# Activate features/Defines

option(DEBUG_FEATURE                                            "Debug mode"                                              ON )
option(XTRACE_FEATURE                                           "XTrace"                                                  ON )
#option(XMEMORY_CONTROL_FEATURE                                  "XMemory Control"                                         ON )
#option(XFEEDBACK_CONTROL_FEATURE                                "XFeedback Control"                                       ON )   

option(USE_CLANG_COMPILER_FEATURE                               "Use Clang Compiler"                                      ON )

option(XPUBLISHER_FEATURE                                       "XPublisher"                                              ON )

option(APPMODE_LIBRARY_STATIC_FEATURE                           "Application Library Static  mode"                        ON )
#option(APPMODE_LIBRARY_DINAMIC_FEATURE                          "Application Library Dinamic mode"                        ON )
    
option(LINUX_VISUALSTUDIO_CP1252_FEATURE                        "Linux CodePage Editor Visual Studio CP1252"              ON )   
                                
option(XLOG_FEATURE                                             "LOG File"                                                ON )  


# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/Common/CMake/GEN_Main.cmake") 

                     
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Sources")
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

 

# --------------------------------------------------------------------
# End Proyect 

include("${GEN_DIRECTORY}/Common/CMake/GEN_End.cmake")

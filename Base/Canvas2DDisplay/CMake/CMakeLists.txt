# --------------------------------------------------------------------
# Canvas2dDisplay : Example of console (Canvas minimal app)
# GEN FrameWork 
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.16.0)

# --------------------------------------------------------------------
# PreProject

set(GEN_DIRECTORY "../../../..") 

option(USE_CLANG_COMPILER_FEATURE                               "Use Clang Compiler"                                      ON)
include("${GEN_DIRECTORY}/Common/CMake/GEN_PreProject.cmake")

project(canvas2ddisplay)

# --------------------------------------------------------------------
# Activate features/Defines

option(DEBUG_FEATURE                                            "Debug mode"                                              ON )
option(XTRACE_FEATURE                                           "XTrace"                                                  ON )
option(XMEMORY_CONTROL_FEATURE                                  "XMemory Control"                                         ON )

                                                                                                
option(DIO_FEATURE                                              "Data Input/Output"                                       ON ) 
option(DIO_STREAM_FEATURE                                       "Data Input/Output Stream"                                ON )
option(DIO_STREAMUART_FEATURE                                   "Data Input/Output Stream UART"                           ON )
option(DIO_STREAMUSB_FEATURE                                    "Data Input/Output Stream USB"                            ON )
                                                              
option(APPFLOW_FEATURE                                          "Application flow modules"                                ON )


# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/Common/CMake/GEN_Main.cmake") 

                     
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Sources")
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/Canvas2DDisplay.cpp")


# --------------------------------------------------------------------
# End Proyect 

include("${GEN_DIRECTORY}/Common/CMake/GEN_End.cmake")

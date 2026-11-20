# --------------------------------------------------------------------
# NetCapture : Example of console of net capture
# GEN FrameWork
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.16.0)

# --------------------------------------------------------------------
# PreProject

set(GEN_DIRECTORY "../../../..") 

option(USE_CLANG_COMPILER_FEATURE                               "Use Clang Compiler"                                      ON)
include("${GEN_DIRECTORY}/Common/CMake/GEN_PreProject.cmake")

project(netcapture)

# --------------------------------------------------------------------
# Activate features/Defines

option(DEBUG_FEATURE                                            "Debug mode"                                              ON )
option(XTRACE_FEATURE                                           "XTrace"                                                  ON )
option(XTRACE_NOINTERNET_FEATURE                                "No need for trace dependencies with Internet"            ON )                  
option(XMEMORY_CONTROL_FEATURE                                  "XMemory Control"                                         ON )

               
option(DIO_FEATURE                                              "Input/Output"                                            ON )
option(DIO_PUBLICINTERNETIP_FEATURE                             "Public Internet IP"                                      ON )
option(DIO_PCAP_FEATURE                                         "PCap Library"                                            ON )

option(APPFLOW_FEATURE                                          "Application Flow modules"                                ON )
option(APPFLOW_EXTENDED_FEATURE                                 "Application Flow Extended"                               ON )  
option(APPFLOW_EXTENDED_APPLICATIONHEADER_FEATURE               "Application Flow Extended Aplication Header"             ON )  
option(APPFLOW_EXTENDED_APPLICATIONSTATUS_FEATURE               "Application Flow Extended Aplication Status"             ON )  
option(APPFLOW_CONSOLE_FEATURE                                  "Application Flow Console"                                ON )
option(APPFLOW_LOG_FEATURE                                      "Application Flow Log"                                    ON )
                                                                              
option(APPFLOW_CFG_GENERAL_FEATURE                              "Application Flow CFG General"                            ON )
option(APPFLOW_CFG_LOG_FEATURE                                  "Application Flow CFG LOG"                                ON )


# --------------------------------------------------------------------
# Config Application Macro

set(APP_CFG_SCRIPTS "-DAPPFLOW_CFG=NETCAPTURE_CFG::GetInstance()")
add_definitions(${APP_CFG_SCRIPTS})


# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/Common/CMake/GEN_Main.cmake")
                   

# --------------------------------------------------------------------
# Directorys of the Application
       
set(APP_DIRECTORY_APPLICATION   "../Sources")
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/NetCapture.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/NetCapture_CFG.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/NetCapture_Sniffer.cpp")
 

# --------------------------------------------------------------------
# End Proyect 

include("${GEN_DIRECTORY}/Common/CMake/GEN_End.cmake")


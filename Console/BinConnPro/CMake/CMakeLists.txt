# --------------------------------------------------------------------
# BinConnPro : Example of console: Binary protocol example
# GEN FrameWork
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.16.0)
project(binconnpro)


set(GEN_DIRECTORY "../../../..") 


# --------------------------------------------------------------------
# features/Defines

option(DEBUG_FEATURE                                            "Debug mode"                                              ON )
option(XTRACE_FEATURE                                           "XTrace"                                                  ON )
option(XTRACE_NOINTERNET_FEATURE                                "No need for trace dependencies with Internet"            ON )
option(XMEMORY_CONTROL_FEATURE                                  "XMemory Control"                                         ON )

option(USE_CLANG_COMPILER_FEATURE                               "Use Clang Compiler"                                      ON )

option(COVERAGE_CREATEINFO_FEATURE                              "Coverage - Create Info"                                  ON ) 
option(COVERAGE_GENERATESHOWINFO_FEATURE                        "Coverage - Generate Show Info"                           ON ) 
                    
option(DIO_FEATURE                                              "Data Input/Output"                                       ON ) 
option(DIO_CHECKCONNECTIONS_FEATURE                             "Check Connections"                                       ON )
option(DIO_NETWORKTIMEPROTOCOL_FEATURE                          "Network Time Protocol"                                   ON )
option(DIO_DYNDNS_FEATURE                                       "DynDNS"                                                  ON )


option(DIO_PROTOCOL_FEATURE                                     "Data Input/Output Protocol"                              ON )
    
option(APPFLOW_FEATURE                                          "Application Flow modules"                                ON )
option(APPFLOW_CONSOLE_FEATURE                                  "Application Flow Console"                                ON )
option(APPFLOW_EXTENDED_FEATURE                                 "Application Flow Extended"                               ON )  
option(APPFLOW_EXTENDED_APPLICATIONHEADER_FEATURE               "Application Flow Extended Aplication Header"             ON )  
option(APPFLOW_EXTENDED_APPLICATIONSTATUS_FEATURE               "Application Flow Extended Aplication Status"             ON )  
option(APPFLOW_EXTENDED_INTERNETSTATUS_FEATURE                  "Application Flow Extended Internet Status"               ON )  
option(APPFLOW_CHECKRESOURCESHARDWARE_FEATURE                   "Application Flow Check Resources Hardwar"                ON )
option(APPFLOW_INTERNETSERVICES_FEATURE                         "Application Flow Internet Services"                      ON )
option(APPFLOW_LOG_FEATURE                                      "Application Flow Log"                                    ON )
                                                                              
option(APPFLOW_CFG_GENERAL_FEATURE                              "Application Flow CFG General"                            ON )  
option(APPFLOW_CFG_LOG_FEATURE                                  "Application Flow CFG LOG"                                ON )
option(APPFLOW_CFG_INTERNETSERVICES_FEATURE                     "Application Flow CFG Internet services"                  ON )      
option(APPFLOW_CFG_CHECKRESOURCESHARDWARE_FEATURE               "Application Flow CFG Check Resorces HW"                  ON )  
option(APPFLOW_CFG_DNSRESOLVER_FEATURE                          "Application Flow CFG DNS "                               ON )   
option(APPFLOW_CFG_DIOLOCATION_FEATURE                          "Application Flow CFG DIO Location"                       ON )          

# --------------------------------------------------------------------
# Config Application Macro

set(APP_CFG_BINCONNPRO "-DAPPFLOW_CFG=BINCONNPRO_CFG::GetInstance()")
add_definitions(${APP_CFG_BINCONNPRO})


# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/Common/CMake/GEN_Main.cmake") 
                   
                   
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Sources")
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/BinConnPro.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/BinConnPro_CFG.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/BinConnPro_ApplicationData.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/BinConnPro_ConnectionsManager.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/BinConnPro_Protocol.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/BinConnPro_Protocol_Device.cpp")


# --------------------------------------------------------------------
# End Proyect 

include("${GEN_DIRECTORY}/Common/CMake/GEN_End.cmake")

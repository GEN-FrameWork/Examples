# --------------------------------------------------------------------
# MiniWebServer : Example of console: Web Server example
# GEN FrameWork
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.16.0)
project(miniwebserver)


set(GEN_DIRECTORY "../../../..") 


# --------------------------------------------------------------------
# Activate features/Defines

option(DEBUG_FEATURE                                            "Debug mode"                                              ON )
option(XMEMORY_CONTROL_FEATURE                                  "XMemory Control"                                         ON )
option(XTRACE_FEATURE                                           "XTrace"                                                  ON )
option(XTRACE_NOINTERNET_FEATURE                                "No need for trace dependencies with Internet"            ON )

option(USE_CLANG_COMPILER_FEATURE                               "Use Clang Compiler"                                      ON )

option(XSERIALIZABLE_JSON_FEATURE                               "Serializable JSON"                                       ON ) 
                    
option(DIO_FEATURE                                              "Input/Output"                                            ON )
option(DIO_PING_NATIVE_FEATURE                                  "Ping Native"                                             ON )  
option(DIO_PUBLICINTERNETIP_FEATURE                             "Public Internet IP"                                      ON )
option(DIO_CHECKCONNECTIONS_FEATURE                             "Check Connections"                                       ON )
option(DIO_NETWORKTIMEPROTOCOL_FEATURE                          "Network Time Protocol"                                   ON )
option(DIO_DYNDNS_FEATURE                                       "DynDNS"                                                  ON )
option(DIO_WEBSERVER_FEATURE                                    "Web Server"                                              ON )
    
option(APPFLOW_FEATURE                                          "Application Flow modules"                                ON )
option(APPFLOW_CONSOLE_FEATURE                                  "Application Flow Console"                                ON )
option(APPFLOW_LOG_FEATURE                                      "Application Flow Log"                                    ON )
option(APPFLOW_EXTENDED_FEATURE                                 "Application Flow Extended"                               ON )  
option(APPFLOW_EXTENDED_APPLICATIONHEADER_FEATURE               "Application Flow Extended Aplication Header"             ON )  
option(APPFLOW_EXTENDED_APPLICATIONSTATUS_FEATURE               "Application Flow Extended Aplication Status"             ON )  
option(APPFLOW_EXTENDED_INTERNETSTATUS_FEATURE                  "Application Flow Extended Internet Status"               ON )  
option(APPFLOW_WEBSERVER_FEATURE                                "Application Flow Web Server"                             ON )
              
option(APPFLOW_CFG_GENERAL_FEATURE                              "Application Flow CFG General"                            ON )
option(APPFLOW_CFG_LOG_FEATURE                                  "Application Flow CFG LOG"                                ON )
option(APPFLOW_CFG_CHECKRESOURCESHARDWARE_FEATURE               "Application Flow CFG Check Resorces HW"                  ON )  
option(APPFLOW_CFG_INTERNETSERVICES_FEATURE                     "Application Flow CFG Internet services"                  ON )
option(APPFLOW_CFG_DYNDNSMANAGER_FEATURE                        "Application Flow CFG DynDNS Manager"                     ON )
option(APPFLOW_CFG_WEBSERVER_FEATURE                            "Application Flow CFG Web Server"                         ON )


# --------------------------------------------------------------------
# Config Application Macro

set(APP_CFG_MINISERVERWEB "-DAPPFLOW_CFG=MINIWEBSERVER_CFG::GetInstance()")
add_definitions(${APP_CFG_MINISERVERWEB})


# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/Common/CMake/GEN_Main.cmake") 
                   
                   
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Sources")
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/MiniWebServer.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/MiniWebServer_CFG.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/MiniWebServer_APIRest.cpp")


# --------------------------------------------------------------------
# End Proyect 

include("${GEN_DIRECTORY}/Common/CMake/GEN_End.cmake")

 
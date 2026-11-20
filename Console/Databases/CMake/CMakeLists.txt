# --------------------------------------------------------------------
# DataBases : Example of console: Databases connector example
# GEN FrameWork
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.16.0)

# --------------------------------------------------------------------
# PreProject

set(GEN_DIRECTORY "../../../..") 

option(USE_CLANG_COMPILER_FEATURE                               "Use Clang Compiler"                                      ON)
include("${GEN_DIRECTORY}/Common/CMake/GEN_PreProject.cmake")

project(databases)

# --------------------------------------------------------------------
# Activate features/Defines

option(DEBUG_FEATURE                                            "Debug mode"                                              ON )
option(XTRACE_FEATURE                                           "XTrace"                                                  ON )
option(XTRACE_NOINTERNET_FEATURE                                "No need for trace dependencies with Internet"            ON )
option(XMEMORY_CONTROL_FEATURE                                  "XMemory Control"                                         ON )

                    
option(DIO_FEATURE                                              "Input/Output"                                            ON )
option(DIO_PUBLICINTERNETIP_FEATURE                             "Public Internet IP"                                      ON )

option(APPFLOW_FEATURE                                          "Application Flow modules"                                ON )
option(APPFLOW_EXTENDED_APPLICATIONHEADER_FEATURE               "Application Flow Extended Aplication Header"             ON )  
option(APPFLOW_EXTENDED_APPLICATIONSTATUS_FEATURE               "Application Flow Extended Aplication Status"             ON )  
option(APPFLOW_CONSOLE_FEATURE                                  "Application Flow Console"                                ON )
option(APPFLOW_LOG_FEATURE                                      "Application Flow Log"                                    ON )
                                                                                
option(APPFLOW_CFG_GENERAL_FEATURE                              "Application Flow CFG General"                            ON )
option(APPFLOW_CFG_LOG_FEATURE                                  "Application Flow CFG LOG"                                ON )    

option(DATABASES_SQL_FEATURE                                    "DataBases SQL"                                           ON )
option(DATABASES_SQL_SQLITE_FEATURE                             "DataBases SQLite"                                        ON )
option(DATABASES_SQL_MYSQL_FEATURE                              "DataBases MySQL"                                         ON )
option(DATABASES_SQL_POSTGRESQL_FEATURE                         "DataBases PostgreSQL"                                    ON )


# --------------------------------------------------------------------
# Config Application Macro

set(APP_CFG_DATABASES "-DAPPFLOW_CFG=DATABASES_CFG::GetInstance()")
add_definitions(${APP_CFG_DATABASES})


# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/Common/CMake/GEN_Main.cmake") 
                   
                   
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Sources")
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/Databases.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/Databases_CFG.cpp")


# --------------------------------------------------------------------
# End Proyect 

include("${GEN_DIRECTORY}/Common/CMake/GEN_End.cmake")

# --------------------------------------------------------------------
# Canvas2d : Example of graphics Canvas 2D example  
# GEN FrameWork 
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.16.0)
project(canvas2d)


set(GEN_DIRECTORY "../../../..") 


option(DEBUG_FEATURE                                            "Debug mode"                                              ON )
option(XTRACE_FEATURE                                           "XTrace"                                                  ON )
#option(XTRACE_NOINTERNET_FEATURE                                "No need for trace dependencies with Internet"            ON )
option(XTHREADCOLLECTED_FEATURE                                 "Thread Collected"                                        ON )
option(XMEMORY_CONTROL_FEATURE                                  "XMemory Control"                                         ON )

option(USE_CLANG_COMPILER_FEATURE                               "Use Clang Compiler"                                      ON )

option(GRP_OPENGL_FEATURE                                       "Graphics Open GL"                                        ON )

option(LINUX_X11_FEATURE                                        "Linux X11"                                               ON )
#option(LINUX_WAYLAND_FEATURE                                    "Linux WAYLAND"                                           ON )

        
option(APPFLOW_FEATURE                                          "Application Flow modules"                                ON )
option(APPFLOW_EXTENDED_FEATURE                                 "Application Flow Extended"                               ON )  
option(APPFLOW_LOG_FEATURE                                      "Application Flow Log"                                    ON )
option(APPFLOW_GRAPHICS_FEATURE                                 "Application Flow Graphics"                               ON )
option(APPFLOW_GRAPHICS_NOTCONSOLE_FEATURE                      "Application Flow Graphics (Deactive Console)"            ON ) 
option(APPFLOW_CFG_GENERAL_FEATURE                              "Application Flow CFG General"                            ON )  
option(APPFLOW_CFG_LOG_FEATURE                                  "Application Flow CFG LOG"                                ON )

option(GRP_FEATURE                                              "Graphics"                                                ON )
#option(GRP_SCREEN_CUSTOMCHROMES_FEATURE                         "Graphics Screen Custom Chromes"                          ON )
option(GRP_BITMAP_FILE_BMP_FEATURE                              "Graphics Bitmap File BMP"                                ON )
option(GRP_BITMAP_FILE_JPG_FEATURE                              "Graphics Bitmap File JPG"                                ON )
option(GRP_BITMAP_FILE_PNG_FEATURE                              "Graphics Bitmap File PNG"                                ON )
option(GRP_BITMAP_FILE_TGA_FEATURE                              "Graphics Bitmap File TGA"                                ON )
option(GRP_2D_FEATURE                                           "Graphics 2D"                                             ON )

option(INP_FEATURE                                              "Inputs"                                                  ON )

option(SND_FEATURE                                              "Sound"                                                   ON )
option(SND_FILE_WAV_FEATURE                                     "Sound WAV file"                                          ON )
option(SND_FILE_OGG_FEATURE                                     "Sound OGG file"                                          ON )


# --------------------------------------------------------------------
# Config Application Macro

set(APP_CFG_CANVAS2D "-DAPPFLOW_CFG=CANVAS2D_CFG::GetInstance()")
add_definitions(${APP_CFG_CANVAS2D})


# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/Common/CMake/GEN_Main.cmake") 
                   
                   
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Sources")
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/Canvas2D.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/Canvas2D_CFG.cpp")


# --------------------------------------------------------------------
# End Proyect 

include("${GEN_DIRECTORY}/Common/CMake/GEN_End.cmake")


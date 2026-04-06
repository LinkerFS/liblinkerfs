CMAKE_MINIMUM_REQUIRED(VERSION 3.21)
project(liblinkerfs LANGUAGES C)
set(CMAKE_C_STANDARD 99)

if (${PROJECT_IS_TOP_LEVEL})
    set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
else ()
    set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
endif ()

if (NOT DEFINED BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ON)
endif ()

option(LIBLINKERFS_ENABLE_UDF "Enable UDF support for liblinkerfs" OFF)
#configuration of msys2 for windows build, when enable UDF support
set(MSYS_SYSTEM "MINGW64" CACHE STRING "Build environment, one of MINGW64 MINGW32 CLANG64 UCRT64")
set(MSYS_PATH "C:/msys64" CACHE PATH "Root directory of msys2")

add_subdirectory(src)
add_subdirectory(depends)
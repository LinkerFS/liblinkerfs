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

set(ENABLE_FEATURE_UDF OFF)
add_subdirectory(src)
add_subdirectory(depends)
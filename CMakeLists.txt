CMAKE_MINIMUM_REQUIRED(VERSION 3.21)
project(liblinkerfs LANGUAGES C)
set(CMAKE_CXX_STANDARD 99)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src)

set(SOURCES
        src/generator.c
)
set(EXPORT_HEADERS
        src/generator.h
        src/data/warp.h
)
set(LIBRARY_OUTPUT_PATH  ${PROJECT_BINARY_DIR}/lib)


add_library(liblinkerfs_shared SHARED ${SOURCES})
add_library(liblinkerfs_static STATIC ${SOURCES})
set_target_properties(liblinkerfs_shared PROPERTIES PREFIX "" OUTPUT_NAME "linkerfs")
set_target_properties(liblinkerfs_static PROPERTIES OUTPUT_NAME "linkerfs" )

file(COPY ${EXPORT_HEADERS} DESTINATION ${PROJECT_BINARY_DIR}/include)
include(GenerateExportHeader)

if (NOT BUILD_SHARED_LIBS)
    add_definitions(-DLIBLINKERFS_BUILD_STATIC)
endif ()

set(LIBLINKERFS_EXPORT_FILE "liblinkerfs_export.h")
set(EXPORT_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/liblinkerfs)
set(LIBLINKERFS_EXPORT ${CMAKE_CURRENT_BINARY_DIR}/${LIBLINKERFS_EXPORT_FILE})
set(HEADERS
        log/log.h
        include/liblinkerfs/data/warp.h
        include/liblinkerfs/log/log_config.h
        include/liblinkerfs/generator.h
utils        include/liblinkerfs/utils/algorithm.h
)

set(SOURCES
        generator.c
        log/log.c
        utils/algorithm.c
)

add_library(liblinkerfs ${SOURCES} ${HEADERS})
set_target_properties(liblinkerfs PROPERTIES OUTPUT_NAME "linkerfs")
target_include_directories(liblinkerfs PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include/liblinkerfs
        ${PROJECT_SOURCE_DIR}
)
generate_export_header(liblinkerfs
        EXPORT_FILE_NAME ${LIBLINKERFS_EXPORT_FILE}
        BASE_NAME "LIBLINKERFS"
        EXPORT_MACRO_NAME "PUBLIC"
        DEPRECATED_MACRO_NAME "DEPRECATED"
        NO_EXPORT_MACRO_NAME "PRIVATE"
        STATIC_DEFINE "BUILD_STATIC"
        PREFIX_NAME "LIBLINKERFS_"
        INCLUDE_GUARD_NAME "LIBLINKERFS_EXPORT_H"
        DEFINE_NO_DEPRECATED
)

file(COPY ${LIBLINKERFS_EXPORT} DESTINATION ${EXPORT_HEADERS})
if (${PROJECT_IS_TOP_LEVEL})
    file(COPY ${EXPORT_HEADERS} DESTINATION ${CMAKE_BINARY_DIR}/include)
endif ()
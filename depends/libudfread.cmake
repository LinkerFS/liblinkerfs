find_library(LIB_udfread NAMES udfread PATHS ${CMAKE_CURRENT_SOURCE_DIR}/binary/libudfread/lib NO_CACHE NO_CMAKE_SYSTEM_PATH)

if (LIB_udfread)
    message(STATUS "Found Library udfread: ${LIB_udfread}")
    add_library(libudfread UNKNOWN IMPORTED GLOBAL)
    set_target_properties(libudfread PROPERTIES IMPORTED_LOCATION ${LIB_udfread})
    target_include_directories(libudfread INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/binary/libudfread/include)
else ()
    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/libudfread/src)
        include(ExternalProject)
        set(libudfread_INCLUDE_DIR ${CMAKE_BINARY_DIR}/libudfread/include)
        set(libudfread_LIB libudfread.a)
        if (BUILD_SHARED_LIBS)
            if (CMAKE_IMPORT_LIBRARY_SUFFIX)
                set(libudfread_LIB libudfread${CMAKE_IMPORT_LIBRARY_SUFFIX})
            else ()
                set(libudfread_LIB libudfread.so)
            endif ()
        endif ()

        ExternalProject_Add(libudfread_build
                SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libudfread
                CONFIGURE_COMMAND autoreconf -vif <SOURCE_DIR> && ${CMAKE_CURRENT_SOURCE_DIR}/libudfread/configure --prefix=${CMAKE_BINARY_DIR}/libudfread
                BUILD_COMMAND make -j${nproc}
                INSTALL_COMMAND make -j${nproc} install
                BUILD_BYPRODUCTS ${CMAKE_BINARY_DIR}/libudfread/lib/${libudfread_LIB}
        )
        file(MAKE_DIRECTORY ${libudfread_INCLUDE_DIR})
        add_library(libudfread UNKNOWN IMPORTED GLOBAL)
        add_dependencies(libudfread libudfread_build)
        set_target_properties(libudfread
                PROPERTIES IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/libudfread/lib/${libudfread_LIB}
                INTERFACE_INCLUDE_DIRECTORIES ${libudfread_INCLUDE_DIR}
        )
    else ()
        message(FATAL_ERROR "Not Found libudfread, use 'git submodule update --init --recursive' first!")
    endif ()
endif ()


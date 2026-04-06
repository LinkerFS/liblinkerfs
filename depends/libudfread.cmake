if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/libudfread/src)
    include(ExternalProject)
    set(libudfread_INCLUDE_DIR ${CMAKE_BINARY_DIR}/libudfread/include)
    set(libudfread_LIB libudfread-linkerfs.a)
    if (BUILD_SHARED_LIBS)
        if (CMAKE_IMPORT_LIBRARY_SUFFIX)
            set(libudfread_LIB libudfread-linkerfs.dll.a)
        else ()
            set(libudfread_LIB libudfread-linkerfs.so)
        endif ()
    endif ()
    set(CONFIGURE_COMMAND cd <SOURCE_DIR> && autoconf -vif && cd - && <SOURCE_DIR>/configure --prefix=${CMAKE_BINARY_DIR}/libudfread)
    set(BUILD_COMMAND make -j${nproc})
    set(INSTALL_COMMAND make -j${nproc} install)
    if (WIN32)
        find_program(MSYS_BASH NAMES bash.exe PATHS "${MSYS_PATH}/usr/bin")
        if (NOT MSYS_BASH)
            message(FATAL_ERROR "Not Found msys2!")
        endif ()
        set(CONFIGURE_COMMAND ${CMAKE_COMMAND} -E env MSYSTEM=${MSYS_SYSTEM} CHERE_INVOKING=1
                ${MSYS_BASH} -lc "cd $(cygpath <SOURCE_DIR>) && autoconf -vif && cd - && $(cygpath <SOURCE_DIR>)/configure --prefix=${CMAKE_BINARY_DIR}/libudfread")
        set(BUILD_COMMAND ${CMAKE_COMMAND} -E env MSYSTEM=${MSYS_SYSTEM} CHERE_INVOKING=1
                ${MSYS_BASH} -lc "make -j${nproc}")
        set(INSTALL_COMMAND ${CMAKE_COMMAND} -E env MSYSTEM=${MSYS_SYSTEM} CHERE_INVOKING=1
                ${MSYS_BASH} -lc "make -j${nproc} install")
    endif ()
    ExternalProject_Add(libudfread_build
            SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libudfread
            CONFIGURE_COMMAND ${CONFIGURE_COMMAND}
            BUILD_COMMAND ${BUILD_COMMAND}
            INSTALL_COMMAND ${INSTALL_COMMAND}
            BUILD_BYPRODUCTS ${CMAKE_BINARY_DIR}/libudfread/lib/${libudfread_LIB}
    )
    file(MAKE_DIRECTORY ${libudfread_INCLUDE_DIR})
    add_library(libudfread-linkerfs UNKNOWN IMPORTED GLOBAL)
    add_dependencies(libudfread-linkerfs libudfread_build)
    set_target_properties(libudfread-linkerfs
            PROPERTIES IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/libudfread/lib/${libudfread_LIB}
            INTERFACE_INCLUDE_DIRECTORIES ${libudfread_INCLUDE_DIR}
    )
    install(FILES ${CMAKE_BINARY_DIR}/libudfread/lib/${libudfread_LIB} DESTINATION lib)
    install(DIRECTORY ${libudfread_INCLUDE_DIR}/udfread DESTINATION include)
else ()
    message(FATAL_ERROR "Not Found libudfread, use 'git submodule update --init --recursive' first!")
endif ()
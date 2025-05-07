set(HEADERS
    ../../include/liblinkerfs/udf/udf.h
)
set(SOURCES
    udf.c
)
target_sources(liblinkerfs PRIVATE ${HEADERS} ${SOURCES})
target_link_libraries(liblinkerfs PUBLIC libudfread)
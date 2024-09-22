file(GLOB SRC "*.c")
# set(MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/main.c)
# string(REGEX REPLACE ${MAIN_SRC} "" SRC ${SRC})

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME SUBPROJECT_NAME)   
string(REPLACE " " "_" SUBPROJECT_NAME ${SUBPROJECT_NAME})
add_executable(${SUBPROJECT_NAME} ${SRC})

target_compile_definitions(${SUBPROJECT_NAME} PUBLIC
    $<IF:$<CONFIG:DEBUG>,_DEBUG,NDEBUG>
)

target_include_directories(${SUBPROJECT_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${DEV_SYS_INCLUDE}"
)

target_compile_options(${SUBPROJECT_NAME} PRIVATE
    -Wall
)

if(WIN32)
    target_compile_definitions(${SUBPROJECT_NAME} PRIVATE
        _UNICODE
        UNICODE
    )
endif()

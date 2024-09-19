cmake_minimum_required(VERSION 3.28)

cmake_path(GET CMAKE_SOURCE_DIR FILENAME ROOT_NAME)
string(REPLACE " " "_" ${ROOT_NAME} ${ROOT_NAME})
project(${ROOT_NAME}
    LANGUAGES C CXX
)

option(BUILD_TEST_TEMPLATE "Ignore warnings related to TODOs" OFF)
option(ENABLE_CODE_ANALYSIS "Use Static Code Analysis on build" OFF)

add_subdirectory(src)

enable_testing()
add_subdirectory(test)

cmake_minimum_required (VERSION 3.28)

cmake_path(GET CMAKE_SOURCE_DIR FILENAME ROOT_NAME)
string(REPLACE " " "_" ${ROOT_NAME} ${ROOT_NAME})
project(${ROOT_NAME}
    LANGUAGES C CXX
)

option(BUILD_TEST_TEMPLATE "Ignore warnings related to TODOs" OFF)

option(ENABLE_CODE_ANALYSIS "Use Static Code Analysis on build" OFF)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_subdirectory(src)
add_subdirectory(test)

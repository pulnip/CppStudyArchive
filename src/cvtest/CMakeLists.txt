cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME SUB_PROJECT_NAME)
string(REPLACE " " "_" SUB_PROJECT_NAME ${SUB_PROJECT_NAME})

file(GLOB ${SUB_PROJECT_NAME}_SRC "*.cpp")

add_executable(${SUB_PROJECT_NAME}
    ${${SUB_PROJECT_NAME}_SRC}
)

target_compile_definitions(${SUB_PROJECT_NAME} PUBLIC
    $<IF:$<CONFIG:DEBUG>, _DEBUG, NDEBUG>
    _UNICODE UNICODE
)

target_include_directories(${SUB_PROJECT_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${MINGW_INCLUDE}"
)

target_compile_options(${SUB_PROJECT_NAME} PRIVATE
    -Wall -Wextra
)

target_link_libraries(${SUB_PROJECT_NAME} PRIVATE
    stdc++exp
)

find_package(OpenCV CONFIG REQUIRED
    core imgcodecs highgui
)
if(OPENCV_CORE_FOUND AND OPENCV_IMGCODECS_FOUND AND
    OPENCV_HIGHGUI_FOUND
)
    message(STATUS "Using OpenCV")
    target_include_directories(${SUB_PROJECT_NAME} PRIVATE
        ${OpenCV_INCLUDE_DIRS}
    )
    target_link_libraries(${SUB_PROJECT_NAME} PRIVATE
        ${OpenCV_LIBS}
    )
endif()

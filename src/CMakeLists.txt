file(GLOB MAIN_SRC "*.cpp")

add_executable(${PROJECT_NAME}
    ${MAIN_SRC}
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    $<IF:$<CONFIG:DEBUG>,_DEBUG,NDEBUG>
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${DEV_SYS_INCLUDE}"
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall -Wextra
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    stdc++exp
)

find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${OpenCV_LIBS}
    )
endif()

if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        _UNICODE
        UNICODE
    )
endif()

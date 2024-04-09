cmake_minimum_required(VERSION 3.20)

project(visualizer)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletest)

# set sources here
set(SOURCES

)

# set test sources here
set(TEST_SOURCES
    test/test.cpp
)

add_executable(visualizer ${SOURCES} ${TEST_SOURCES})
target_link_libraries(visualizer gtest gtest_main)

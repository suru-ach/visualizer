cmake_minimum_required(VERSION 3.10)

project(Lox)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletest)

set(SOURCES
    src/lox.cpp
    src/scanner.cpp
    src/token.cpp
    src/astprinter.cpp
    src/parser.cpp
)

set(TEST_SOURCES
    test/test.cpp
)

add_executable(lox ${SOURCES} ${TEST_SOURCES})

target_link_libraries(lox gtest gtest_main)

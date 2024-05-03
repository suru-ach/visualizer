cmake_minimum_required(VERSION 3.10)

project(Lox)

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletest)

set(SOURCES
    src/lox.cpp
    src/scanner.cpp
    src/token.cpp
    #src/astprinter.cpp
    src/parser.cpp
)

set(TEST_SOURCES
    test/test.cpp
)

add_executable(lox ${SOURCES} ${TEST_SOURCES})

# then add the custom command to copy it
add_custom_command(
  TARGET lox 
  POST_BUILD
  COMMAND ${CMAKE_COMMAND}
  ARGS -E copy $<TARGET_FILE:lox> ../web2
  )
#target_link_libraries(lox gtest gtest_main)

cmake_minimum_required(VERSION 3.10)
project(FourProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add library for Four class
add_library(${CMAKE_PROJECT_NAME}_lib src/seven.cpp)

# Add executable for the main program (if needed)
add_executable(${CMAKE_PROJECT_NAME}.out src/main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME}.out PRIVATE ${CMAKE_PROJECT_NAME}_lib)

# Add test executable
enable_testing()

add_executable(tests tests/tests_01.cpp)
target_link_libraries(tests PRIVATE ${CMAKE_PROJECT_NAME}_lib gtest_main)

# Add tests to test suite
add_test(NAME FourTests COMMAND tests)
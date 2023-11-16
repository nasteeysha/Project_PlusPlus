project(CPP1_S21_MATRIXPLUS-1)

cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)

add_definitions(
        -Wall
        -Wextra
        -Werror
        -std=c++17
)

include_directories(.)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        TEST1
        test.cc
        s21_matrix_oop.cc
)

target_link_libraries(
        TEST1
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(TEST1)

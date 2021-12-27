cmake_minimum_required(VERSION 3.20)
project(task2)
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()


#include_directories(${PROJECT_SOURCE_DIR}/CMakeProject2)

add_executable (CMakeTest "CMakeTest.cpp" hash.cpp hash.h)

target_link_libraries(CMakeTest gtest_main)
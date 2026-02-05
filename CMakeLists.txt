cmake_minimum_required(VERSION 3.20)
project(iq_baseband_visualizer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(iq_lib
  src/calculatePoint.cpp
)
target_include_directories(iq_lib PUBLIC include)

add_executable(iq_app
  src/main.cpp
)
target_link_libraries(iq_app PRIVATE iq_lib)

# --- Testing ---
include(CTest)
enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(iq_tests
  tests/test_calculatePoint.cpp
)
target_link_libraries(iq_tests PRIVATE iq_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(iq_tests)

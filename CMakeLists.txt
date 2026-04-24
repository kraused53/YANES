cmake_minimum_required( VERSION 3.20 )
project( YANES LANGUAGES CXX )

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin )

include( CTest )

# Bring in my logger library
include( FetchContent )

FetchContent_Declare(
    cpp_logger
    GIT_REPOSITORY https://github.com/kraused53/CppLogger.git
    GIT_TAG master
)

FetchContent_MakeAvailable( cpp_logger )

# Core
add_library(
    YANES_CORE
    src/core/bus/Bus.cpp
    src/core/bus/IBus.cpp
    src/core/cpu/CPU.cpp
)
target_include_directories( YANES_CORE PUBLIC ${PROJECT_SOURCE_DIR}/src )
target_link_libraries( YANES_CORE PRIVATE cpp_logger::cpp_logger )

# IO

# PPU

# APU


# Main executable
add_executable( yanes src/main.cpp )
target_link_libraries(
    yanes
    PRIVATE
        cpp_logger::cpp_logger
        YANES_CORE
)

if(BUILD_TESTING)
    include(FetchContent)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_executable(
        cpu_tests
        tests/cpu/cpu_testing.cpp
    )

    target_link_libraries(
        cpu_tests
        PRIVATE
            cpp_logger::cpp_logger
            YANES_CORE
            GTest::gtest
            GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(cpu_tests)
endif()
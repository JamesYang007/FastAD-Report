cmake_minimum_required (VERSION 3.1.0)
project (Examples)

find_package(Eigen3 3.3 REQUIRED HINTS ${CMAKE_CURRENT_SOURCE_DIR}/libs/eigen-3.3.7/build)
find_package(FastAD CONFIG REQUIRED HINTS ${CMAKE_CURRENT_SOURCE_DIR}/libs/FastAD/build)
if (Eigen3_FOUND)
    message(STATUS "Eigen3 found in ${Eigen3_DIR}")
endif()
if (FastAD_FOUND)
    message(STATUS "FastAD found in ${FastAD_DIR}")
endif()

set(EXAMPLES_LIBS Eigen3::Eigen FastAD::FastAD)

add_subdirectory(src)

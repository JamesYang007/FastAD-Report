cmake_minimum_required (VERSION 3.1.0)
project (Examples)

find_package(Eigen3 3.3 REQUIRED HINTS libs/eigen-3.3.9/build/share)
find_package(FastAD REQUIRED HINTS libs/FastAD/build/share)

set(EXAMPLES_LIBS Eigen3::Eigen FastAD::FastAD)

add_subdirectory(src)

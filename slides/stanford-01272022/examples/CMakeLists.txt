cmake_minimum_required (VERSION 3.1.0)
project (Examples)

find_package(Eigen3 3.3 REQUIRED HINTS libs/eigen-3.3.9/build)
find_package(FastAD CONFIG REQUIRED HINTS libs/FastAD/build)

set(EXAMPLES_LIBS Eigen3::Eigen FastAD::FastAD)

add_subdirectory(src)

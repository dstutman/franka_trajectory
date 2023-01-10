cmake_minimum_required(VERSION 3.13)
project(franka_trajectory)
set(CMAKE_CXX_STANDARD 20)

option(BUILD_TESTS "Build tests" OFF)
option(BUILD_EXAMPLES "Build example code" ON)
add_subdirectory(vendor/libfranka)

add_executable(franka_trajectory
    src/main.cpp)

# Dependencies
## Find Eigen
list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/vendor/libfranka/cmake")
find_package(Eigen3)

## Link deps
target_link_libraries(franka_trajectory Eigen3::Eigen3 Franka::Franka)
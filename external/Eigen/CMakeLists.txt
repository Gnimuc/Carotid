include(FetchContent)

FetchContent_Declare(
    Eigen3
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG        9df21dc8b4b576a7aa5c0094daa8d7e8b8be60f0 # 3.4.x
    GIT_SHALLOW    TRUE
)

message(STATUS "Fetching Eigen...")

FetchContent_MakeAvailable(Eigen3)

set(EIGEN_BUILD_TESTING OFF)
set(EIGEN_SPLIT_LARGE_TESTS OFF)
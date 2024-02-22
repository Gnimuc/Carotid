include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.2
)

message(STATUS "Fetching Catch2...")

FetchContent_MakeAvailable(Catch2)
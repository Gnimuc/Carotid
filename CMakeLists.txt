cmake_minimum_required(VERSION 3.21)

project(Carotid LANGUAGES CXX)

# Turn on using VS solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Modules
include(cmake/utils.cmake)
include(cmake/options.cmake)

# External Dependencies
add_subdirectory(external/Eigen)
add_subdirectory(external/spdlog)

# Core Library
add_library(Carotid SHARED)

add_subdirectory(src)
add_subdirectory(include)

target_include_directories(Carotid PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>)

target_compile_features(Carotid PRIVATE cxx_std_23)

target_link_libraries(Carotid PRIVATE Eigen3::Eigen spdlog::spdlog)

set_target_properties(Carotid PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

include(cmake/install_config.cmake)

if(CAROTID_BUILD_TESTS)
    enable_testing()
    add_subdirectory(external/Catch2)
    add_subdirectory(tests)
endif()

if (CAROTID_BUILD_DOCS)
    add_subdirectory(docs)
endif()


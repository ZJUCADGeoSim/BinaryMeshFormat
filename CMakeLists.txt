
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(
  BinaryMeshFormat
  VERSION 0.1.0
  LANGUAGES CXX
)
set_property(GLOBAL PROPERTY ALLOW_DUPLICATE_CUSTOM_TARGETS 1)

set(BMF_STANDALONE_PROJECT OFF)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  set(BMF_STANDALONE_PROJECT ON)
endif()

option(BMF_TEST "Enable zjucad::BMF test" ${BMF_STANDALONE_PROJECT})
option(BMF_BUILD_CLI "Build command line tools" ${BMF_STANDALONE_PROJECT})
include(cmake/get_cpm.cmake)

include(./dependencies.cmake)

add_library(zjucad_BMF
  STATIC
  src/bmf.cpp
)
add_library(zjucad::BMF ALIAS zjucad_BMF)
target_include_directories(zjucad_BMF PUBLIC include)
target_link_libraries(zjucad_BMF PUBLIC
  igl::core Eigen3::Eigen)
target_compile_features(zjucad_BMF PUBLIC cxx_std_20)

if(BMF_BUILD_CLI)
  add_executable(BMF_convert src/cli/main.cpp)

  target_link_libraries(BMF_convert zjucad::BMF)
endif()

if(BMF_TEST)
  enable_testing()
  add_subdirectory(tests)
endif()
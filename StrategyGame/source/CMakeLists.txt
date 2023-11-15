# CMakeList.txt : CMake project for StrategyGame, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (StrategyGame "StrategyGame.cpp")
target_include_directories(StrategyGame PUBLIC "../headers")
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET StrategyGame PROPERTY CXX_STANDARD 20)
endif()
# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("StrategyGame")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include sub-projects.
find_package(cppzmq CONFIG REQUIRED)
find_package (glog 0.6.0 REQUIRED)
add_subdirectory ("tests")
set(SOURCES
    "source/StrategyGame.cpp"
    "source/MessageReceiver.cpp"
)

add_executable (StrategyGame  ${SOURCES})

target_link_libraries(StrategyGame PRIVATE cppzmq cppzmq-static glog::glog)
target_include_directories(StrategyGame
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/headers
)


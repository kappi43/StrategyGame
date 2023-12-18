cmake_minimum_required(VERSION 3.14)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

find_package(cppzmq CONFIG REQUIRED)
find_package (Boost 1.83.0 REQUIRED)
set(SOURCES
    "sampleTest.cpp"
    "${PROJECT_SOURCE_DIR}/source/MessageReceiver.cpp"
    "${PROJECT_SOURCE_DIR}/source/GameEngineCore.cpp"
)

add_executable (Tests ${SOURCES})
target_link_libraries(
  Tests
  GTest::gtest_main
  cppzmq
  cppzmq-static
  glog::glog
  Boost::boost
)
target_include_directories(Tests
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/headers
)

include(GoogleTest)
gtest_discover_tests(Tests)
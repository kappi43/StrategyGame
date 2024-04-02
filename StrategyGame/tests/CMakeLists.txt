cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
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

set(SOURCES
    "MessageReceiverTests.cpp"
    "${PROJECT_SOURCE_DIR}/src/source/MessageReceiver.cpp"
    "${PROJECT_SOURCE_DIR}/src/source/GameEngineCore.cpp"
    "${PROJECT_SOURCE_DIR}/src/source/MessageQueue.cpp"
    "${PROJECT_SOURCE_DIR}/src/source/Init.cpp"
    "${PROJECT_SOURCE_DIR}/src/source/InitializeBoard.cpp"
)
add_executable (Tests ${SOURCES}  "GameEngineTests.cpp")
target_link_libraries(
  Tests
  GTest::gtest_main
  GTest::gmock_main
  cppzmq
  cppzmq-static
  glog::glog
  Boost::boost
  protobuf::libprotobuf
  messages
)
target_include_directories(Tests
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/src/headers
        ${PROJECT_SOURCE_DIR}/tests
)

include(GoogleTest)
gtest_discover_tests(Tests)
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
)

add_executable (Tests ${SOURCES}  "GameEngineTests.cpp" ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(
  Tests
  GTest::gtest_main
  cppzmq
  cppzmq-static
  glog::glog
  Boost::boost
  protobuf::libprotobuf
)
target_include_directories(Tests
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/src/headers
        ${protobuf_INCLUDE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
)

include(GoogleTest)
gtest_discover_tests(Tests)
cmake_minimum_required (VERSION 3.10)
project ("StrategyGame")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package (cppzmq CONFIG REQUIRED)
find_package (glog 0.6.0 REQUIRED)

find_package (Boost 1.83.0 REQUIRED)
find_package(protobuf CONFIG REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
SET_SOURCE_FILES_PROPERTIES(PROTO_SRC PROTO_HDRS PROPERTIES GENERATED TRUE)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROJECT_SOURCE_DIR}/protobuf_definitions/InitBoardReq.proto)
add_subdirectory ("tests")


set(SOURCES
    "src/source/StrategyGame.cpp"
    "src/source/MessageReceiver.cpp"
    "src/source/GameEngineCore.cpp"
    "src/source/MessageQueue.cpp"
)
add_executable (StrategyGame  ${SOURCES} ${PROTO_SRCS} ${PROTO_HDRS})

target_link_libraries(StrategyGame PRIVATE cppzmq cppzmq-static glog::glog Boost::boost PUBLIC protobuf::libprotobuf)
target_include_directories(StrategyGame
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/src/headers
        "$<BUILD_INTERFACE:${PROTO_BINARY_DIR}>"
        ${protobuf_INCLUDE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
)



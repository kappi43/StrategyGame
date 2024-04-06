cmake_minimum_required (VERSION 3.10)
project ("StrategyGame")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package (cppzmq CONFIG REQUIRED)
find_package (glog 0.6.0 REQUIRED)
find_package (Boost 1.83.0 REQUIRED)
find_package (protobuf CONFIG REQUIRED)
add_subdirectory ("protobuf_definitions")

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(SOURCES
    "src/main.cpp"
    "src/messageReceiver/MessageReceiver.cpp"
    "src/gameEngine/GameEngineCore.cpp"
    "src/messageQueue/MessageQueue.cpp"
    "src/states/InitializeBoard.cpp"
    "src/states/Init.cpp"
)
add_executable (StrategyGame  ${SOURCES} )

target_link_libraries(StrategyGame PRIVATE cppzmq cppzmq-static glog::glog Boost::boost PUBLIC protobuf::libprotobuf messages)
target_include_directories(StrategyGame
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/src
        "$<BUILD_INTERFACE:${PROTO_BINARY_DIR}>"
        ${ProtobufIncludePath}
)
add_subdirectory ("tests")




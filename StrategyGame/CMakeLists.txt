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
    "src/source/StrategyGame.cpp"
    "src/source/MessageReceiver.cpp"
    "src/source/GameEngineCore.cpp"
    "src/source/MessageQueue.cpp"
    "src/source/InitializeBoard.cpp"
    "src/source/Init.cpp"
)
add_executable (StrategyGame  ${SOURCES} )

target_link_libraries(StrategyGame PRIVATE cppzmq cppzmq-static glog::glog Boost::boost PUBLIC protobuf::libprotobuf messages)
target_include_directories(StrategyGame
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/src/headers
        "$<BUILD_INTERFACE:${PROTO_BINARY_DIR}>"
        ${ProtobufIncludePath}
)
add_subdirectory ("tests")




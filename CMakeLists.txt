cmake_minimum_required(VERSION 3.8)
project(xrpc_cpp)

set(CMAKE_CXX_STANDARD 17)

if (APPLE)
    include_directories(xrpc_cpp /usr/local/Cellar/openssl/1.0.2m/include)
endif ()

set(SOURCE_FILES src/XConfig.h src/Router.h src/XHttpMethod.h src/XrpcRequest.h src/RouterHandlerFactory.h src/RouterHandler.h src/RouterHandler.cpp src/RouterStats.h src/SessionWrapper.h)
add_library(xrpc_cpp ${SOURCE_FILES})
target_link_libraries(xrpc_cpp -lcrypto -lssl -lfolly -lwangle -lproxygenhttpserver -lproxygenlib -lglog -lgflags -ljemalloc -lboost_system -lboost_thread-mt)

add_executable(example_server src/ExampleServer.cpp)
target_link_libraries(example_server xrpc_cpp)
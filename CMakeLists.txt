cmake_minimum_required(VERSION 3.0)
project(xrpc_cpp)

# package information
set(PACKAGE_NAME      "xrpc-cpp")
set(PACKAGE_VERSION   "0.1.0-dev")
set(PACKAGE_STRING    "${PACKAGE_NAME} ${PACKAGE_VERSION}")
set(PACKAGE_TARNAME   "${PACKAGE_NAME}-${PACKAGE_VERSION}")
set(PACKAGE_BUGREPORT "https://github.com/xjdr/xrpc-cpp/issues")

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "-std=c++1y")
endif()

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if (APPLE)
    include_directories(xrpc_cpp /usr/local/Cellar/openssl/1.0.2m/include)
endif ()

if (LINUX)
    include_directories(/usr/local/include)
    link_directories(/usr/local/lib /usr/local/lib64)
endif ()

set(SOURCE_FILES src/XConfig.h src/Router.h src/XHttpMethod.h src/XrpcRequest.h src/RouterHandlerFactory.h src/RouterHandler.h src/RouterHandler.cpp src/RouterStats.h src/SessionWrapper.h)
add_library(xrpc_cpp ${SOURCE_FILES})
target_link_libraries(xrpc_cpp -lcrypto -lssl -lfolly -lwangle -lproxygenhttpserver -lproxygenlib -lglog -lgflags -ljemalloc -lboost_system)

if (APPLE)
    target_link_libraries(xrpc_cpp -lboost_thread-mt)
endif ()

if (LINUX)
    target_link_libraries(xrpc_cpp -lboost_thread -lpthread)
endif ()

## Add an example server for testing
add_executable(example_server src/ExampleServer.cpp)
target_link_libraries(example_server xrpc_cpp)
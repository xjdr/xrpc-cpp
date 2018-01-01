cmake_minimum_required(VERSION 3.8)
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

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "-std=c++1y")
endif()

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if (APPLE)
    link_directories(/usr/local/lib)
    include_directories(/usr/local/include)
    include_directories(xrpc_cpp /usr/local/Cellar/openssl/1.0.2m/include)
endif ()

if (LINUX)
    include_directories(/usr/local/include)
    link_directories(/usr/local/lib /usr/local/lib64)
endif ()

# External dependencies
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/external)

# Location where external projects will be downloaded
set (DOWNLOAD_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/thrid_party"
        CACHE PATH "Location where external projects will be downloaded.")
mark_as_advanced(DOWNLOAD_LOCATION)

#External Deps
include(re2)
include(zlib)
include(jemalloc)
include(protobuf)
include(boringssl)
include(googletest)

set(xrpc_EXTERNAL_LIBRARIES
        ${re2_STATIC_LIBRARIES}
        ${zlib_STATIC_LIBRARIES}
        ${jemalloc_STATIC_LIBRARIES}
        ${protobuf_STATIC_LIBRARIES}
        ${boringssl_STATIC_LIBRARIES}
        )

include_directories(
        ${re2_INCLUDE_DIR}
        ${zlib_INCLUDE_DIR}
        ${jemalloc_INCLUDE_DIR}
        ${protobuf_INCLUDE_DIR}
        ${boringssl_INCLUDE_DIR}
)

set(SOURCE_FILES
        src/XConfig.h
        src/Router.h
        src/XHttpMethod.h
        src/XrpcRequest.h
        src/RouterHandlerFactory.h
        src/RouterHandler.h
        src/RouterHandler.cpp
        src/RouterStats.h
        src/SessionWrapper.h
        src/Route.h)

## Now for the real work
add_library(xrpc_cpp ${SOURCE_FILES})
target_link_libraries(xrpc_cpp -lre2 ${boringssl_STATIC_LIBRARIES} -lfolly -lwangle -lproxygenhttpserver -lproxygenlib -lglog -lgflags -lboost_system)

if (APPLE)
    target_link_libraries(xrpc_cpp -lboost_thread-mt -jemalloc)
endif ()

if (LINUX)
    target_link_libraries(xrpc_cpp -lboost_thread -lpthread)
endif ()

## Add an example server for testing
add_executable(example_server src/ExampleServer.cpp)
target_link_libraries(example_server xrpc_cpp)

## Add an example server for testing
add_executable(xrpc_cpp_test src/RouterTest.cpp src/RouterTest.cpp)
link_libraries(xrpc_cpp_test ${googletest_STATIC_LIBRARIES})
include_directories(xrpc_cpp_test ${googletest_INCLUDE_DIRS})
cmake_minimum_required(VERSION 3.3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Make files for http client.
add_subdirectory(http_client_async)
add_subdirectory(http_client_sync)

# Make files for http server.
add_subdirectory(http_handler)
add_subdirectory(server)

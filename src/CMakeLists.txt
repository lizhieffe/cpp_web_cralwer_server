cmake_minimum_required(VERSION 3.3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(http_handler)
add_subdirectory(server)

#add_executable(web_crawler_server)
#target_link_libraries(web_crawler_server server)


#set(SOURCE_FILES_SERVER
#		src/http_handler/read_file_handler.h
#		src/http_handler/read_file_handler.cpp
#
#		src/interface/http_handler.h
#		
#    src/server/connection.cpp
#    src/server/connection.h
#    src/server/header.h
#    src/server/main.cpp
#    src/server/mime_types.cpp
#    src/server/mime_types.h
#    src/server/reply.cpp
#    src/server/reply.h
#    src/server/request.h
#    src/server/request_handler.cpp
#    src/server/request_handler.h
#    src/server/request_parser.cpp
#    src/server/request_parser.h
#    src/server/server.cpp
#    src/server/server.h
#)
#
#set(SOURCE_FILES_HTTP_SERVER_SYNC
#		src/http_client_sync/main.cpp)
#
#set(SOURCE_FILES_HTTP_SERVER_ASYNC
#		src/http_client_async/main.cpp)
#				
#set(Boost_USE_STATIC_LIBS        OFF) # only find static libs
#set(Boost_USE_MULTITHREADED      ON)
#set(Boost_USE_STATIC_RUNTIME    OFF)
#find_package(Boost 1.58.0 COMPONENTS date_time filesystem system thread)
#
#if(Boost_FOUND)
#    include_directories(${Boost_INCLUDE_DIRS})
#    
#    add_executable(web_crawler_server ${SOURCE_FILES_SERVER})
#    target_link_libraries(web_crawler_server ${Boost_LIBRARIES})
#    
#    add_executable(http_client_sync ${SOURCE_FILES_HTTP_SERVER_SYNC})
#    target_link_libraries(http_client_sync ${Boost_LIBRARIES})
#    
#    add_executable(http_client_async ${SOURCE_FILES_HTTP_SERVER_ASYNC})
#    target_link_libraries(http_client_async ${Boost_LIBRARIES})
#endif()

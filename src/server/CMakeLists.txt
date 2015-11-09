set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(Boost_USE_STATIC_LIBS        OFF) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.58.0 COMPONENTS date_time filesystem system thread)
include_directories(${Boost_INCLUDE_DIRS})
    
set(SOURCE_FILES
    connection.cpp
    connection.h
    header.h
    main.cpp
    mime_types.cpp
    mime_types.h
    reply.cpp
    reply.h
    request.h
    request_handler.cpp
    request_handler.h
    request_parser.cpp
    request_parser.h
    server.cpp
    server.h)
    
add_executable(server 
		${SOURCE_FILES}
)

target_link_libraries(server 
		${Boost_LIBRARIES}
		http_handler
)

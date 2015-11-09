set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(Boost_USE_STATIC_LIBS        OFF) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.58.0 COMPONENTS date_time filesystem system thread)
include_directories(${Boost_INCLUDE_DIRS})
    
set(SOURCE_FILES
    main.cpp)
    
add_executable(http_client_async 
		${SOURCE_FILES}
)

target_link_libraries(http_client_async 
		${Boost_LIBRARIES}
)

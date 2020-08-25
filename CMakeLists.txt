cmake_minimum_required(VERSION 3.5)

project(TCP_server)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES tcp_start.cpp server.cpp socket.cpp)

add_executable(tcp_server ${SOURCE_FILES})

if(WIN32)
  target_link_libraries(tcp_server wsock32 ws2_32)
endif()

if(UNIX)
	target_link_libraries(tcp_server pthread)
endif()

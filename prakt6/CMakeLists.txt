
cmake_minimum_required(VERSION 3.2)

project(prakt6)

set(CMAKE_CXX_STANDARD 17)

add_executable(prakt6 WIN32
	main.cpp
)

add_definitions(-DUNICODE -D_UNICODE)
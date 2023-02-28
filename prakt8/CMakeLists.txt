
cmake_minimum_required(VERSION 3.2)

project(prakt8)

set(CMAKE_CXX_STANDARD 17)

add_executable(prakt8 WIN32
	main.cpp
)

add_definitions(-DUNICODE -D_UNICODE)
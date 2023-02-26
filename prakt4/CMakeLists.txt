
cmake_minimum_required(VERSION 3.2)

project(prakt4)

set(CMAKE_CXX_STANDARD 17)

add_executable(prakt4 WIN32
	main.cpp
)

add_definitions(-DUNICODE -D_UNICODE)
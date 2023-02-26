
cmake_minimum_required(VERSION 3.2)

project(prakt5)

set(CMAKE_CXX_STANDARD 17)

add_executable(prakt5 WIN32
	main.cpp
)

add_definitions(-DUNICODE -D_UNICODE)
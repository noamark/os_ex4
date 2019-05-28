cmake_minimum_required(VERSION 3.12)
project(os_ex4)

set(CMAKE_CXX_STANDARD 11)

add_executable(os_ex4 MemoryConstants.h PhysicalMemory.cpp PhysicalMemory.h VirtualMemory.cpp VirtualMemory.h main.cpp)
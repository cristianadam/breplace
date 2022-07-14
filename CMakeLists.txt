cmake_minimum_required(VERSION 3.16)

project(breplace LANGUAGES CXX)

if(MSVC)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

add_executable(breplace breplace.cpp)

install(TARGETS breplace)

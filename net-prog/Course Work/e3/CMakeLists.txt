cmake_minimum_required(VERSION 3.10)

project(e3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -pthread -Wall -Wextra")

if(APPLE)
  include_directories(/usr/local/include /opt/homebrew/include)
endif()

if(WIN32)
  include_directories(C:/msys64/ucrt64/include C:/msys64/ucrt/include/c++/14.2.0)
endif()

add_executable(callbacks callbacks.cpp)
add_executable(await await.cpp)


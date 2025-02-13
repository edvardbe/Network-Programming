cmake_minimum_required(VERSION 3.10)

project(tcp_examples)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -pthread -Wall -Wextra")

if(APPLE)
  include_directories(/usr/local/include /opt/homebrew/include)
endif()

add_executable(udp udp.cpp)

find_package(OpenSSL)
add_executable(tls tls.cpp)
target_link_libraries(tls OpenSSL::SSL OpenSSL::Crypto)

cmake_minimum_required(VERSION 3.10)

project(e3)

# Common flags for all platforms
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -Wextra")

# For Apple (macOS)
if(APPLE)
  include_directories(/usr/local/include /opt/homebrew/include)
endif()

# For Windows (both 32-bit and 64-bit)
if(WIN32)
    macro(get_WIN32_WINNT version)
        if(CMAKE_SYSTEM_VERSION)
            set(ver ${CMAKE_SYSTEM_VERSION})
            string(REGEX MATCH "^([0-9]+).([0-9])" ver ${ver})
            string(REGEX MATCH "^([0-9]+)" verMajor ${ver})
            # Check for Windows 10, b/c we'll need to convert to hex 'A' for 10.
            if("${verMajor}" MATCHES "10")
                set(verMajor "A")
                string(REGEX REPLACE "^([0-9]+)" ${verMajor} ver ${ver})
            endif()
            # Remove all remaining '.' characters.
            string(REPLACE "." "" ver ${ver})
            # Prepend each digit with a zero.
            string(REGEX REPLACE "([0-9A-Z])" "0\\1" ver ${ver})
            set(${version} "0x${ver}")
        endif()
    endmacro()

    get_WIN32_WINNT(ver)
    add_definitions(-D_WIN32_WINNT=${ver})
  
    # Include directories for Windows
    include_directories(C:/msys64/mingw64/include C:/msys64/mingw64/include/c++/14.2.0)
  
    # Exclude the pthread flag for Windows
    string(REPLACE "-pthread" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

# Add executables
add_executable(callbacks callbacks.cpp)
add_executable(await await.cpp)

# Link with ws2_32 and mswsock
target_link_libraries(await ws2_32 mswsock)
target_link_libraries(callbacks ws2_32 mswsock)

cmake_minimum_required(VERSION 3.14)
project(prayfetch VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -s")
endif()

add_executable(prayfetch 
    src/main.cpp
)

install(TARGETS prayfetch DESTINATION /usr/local/bin)
install(FILES prayfetch.conf DESTINATION /etc)

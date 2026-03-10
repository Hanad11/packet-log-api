cmake_minimum_required(VERSION 3.15)

project(packet-log-api)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Boost REQUIRED COMPONENTS system filesystem)
find_package(Threads REQUIRED)

include_directories(
    include
    ${Boost_INCLUDE_DIRS}
)

add_executable(packet-log-api
    src/main.cpp
)

target_link_libraries(packet-log-api
    ${Boost_LIBRARIES}
    Threads::Threads
)
cmake_minimum_required(VERSION 3.6) 

project(Vana)

add_definitions(-std=c++11 -m32 -DDAEMON)

set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/build/lib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/build/bin")

#### Finding libraries
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(Botan_FIND_VERSION_MAJOR 2)
set(Botan_FIND_VERSION_MINOR 19)
set(Botan_FIND_VERSION_PATCH 3)
set(Botan_FIND_VERSION 2.19.3)

set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.54.0 REQUIRED COMPONENTS filesystem system thread)

find_package(MySQL REQUIRED)
include_directories(${MYSQL_INCLUDE_DIR})

find_package(SOCI REQUIRED)
include_directories(${SOCI_INCLUDE_DIR})

find_package(Lua REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

find_package(botan 2.19.3 REQUIRED)
include_directories(${BOTAN_INCLUDE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/src/common)

add_subdirectory(src)

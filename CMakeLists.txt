cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME aircontrol-server)

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)

add_library(data_exchange
            query.h
            query.cpp
            data_object.h
            data_object.cpp)

target_link_libraries(${PROJECT_NAME}
                        data_exchange)

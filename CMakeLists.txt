cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME aircontrol-server)

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS
            Sql
            REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

set(DATA_EXCHANGE data_exchange)

add_library(${DATA_EXCHANGE}
            support.h
            support.cpp
            data_object.h
            data_object.cpp
            query.h
            query.cpp
            db_controller.h
            db_controller.cpp)

target_link_libraries(${PROJECT_NAME}
                        data_exchange)


target_link_libraries(${DATA_EXCHANGE}
                        Qt5::Sql)

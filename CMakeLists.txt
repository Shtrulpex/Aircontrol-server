cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME aircontrol-server)

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS
            Sql
            REQUIRED)

add_executable(${PROJECT_NAME}
                main.cpp)

set(LIB1 data_exchange)
set(LIB2 tests)

add_library(${LIB1}
            db_controller.h
            db_controller.hpp
            db_controller.cpp
            data_struct.h
            database.h)

add_library(${LIB2}
            tests.h
            tests.cpp)

target_link_libraries(${PROJECT_NAME}
                        ${LIB1}
                        ${LIB2})

target_link_libraries(${LIB1} PUBLIC
                        Qt5::Sql)

target_link_libraries(${LIB2} PUBLIC
                        ${LIB1}
                        Qt5::Sql)

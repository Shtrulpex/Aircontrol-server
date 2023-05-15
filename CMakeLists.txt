cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME aircontrol-server)

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS
            Sql
            REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)


set(LIB1 data_exchange)
set(LIB2 socket)
set(TESTS tests)

add_library(${LIB1}
            db_controller.h
            db_controller.hpp
            db_controller.cpp
            data_struct.h
            database.h)

add_library(${LIB2}
            fields_count.hpp
            getter.hpp
            magic_in
            magic_out
            socket.cpp
            socket.h
            socket.hpp)

target_link_libraries(${LIB1} PUBLIC
                        Qt5::Sql)

add_executable(${PROJECT_NAME}
               main.cpp )

target_link_libraries(${PROJECT_NAME}
                      ${LIB1}
                      ${LIB2}
                      Threads::Threads)


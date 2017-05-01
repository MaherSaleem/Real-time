cmake_minimum_required(VERSION 3.7)
project(Real_time_project)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    headers/connection.h
    headers/semafors.h
    headers/server_signals.h
    headers/setup_configrations.h
    headers/worker.h
    src/connection.c
    src/main.c
    src/semafors.c
    src/server_signals.c
    src/setup_configrations.c
    src/worker.c)

add_executable(Real_time_project ${SOURCE_FILES})
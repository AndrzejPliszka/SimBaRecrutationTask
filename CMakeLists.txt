cmake_minimum_required(VERSION 4.2)
project(SimBaRecrutationTask)

set(CMAKE_CXX_STANDARD 26)

add_executable(SimBaRecrutationTask main.cpp
        TelemetryBlackBox.h
        TelemetryBlackBox.cpp)

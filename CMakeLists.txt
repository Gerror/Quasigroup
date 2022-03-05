cmake_minimum_required(VERSION 3.16)
project(Quasigroup)

set(CMAKE_CXX_STANDARD 11)

include_directories(src/test/cpp src/main/cpp)

add_executable(Quasigroup
        src/main/cpp/main.cpp
        src/main/cpp/IncidenceCube.cpp
        src/main/cpp/IncidenceCube.h
        src/test/cpp/tests.h
        src/test/cpp/tests.cpp
        src/main/cpp/JMQuasigroup.cpp
        src/main/cpp/JMQuasigroup.h
        src/main/cpp/Quasigroup.cpp
        src/main/cpp/Quasigroup.h
        src/main/cpp/Helper.cpp
        src/main/cpp/Helper.h
        src/main/cpp/PFQuasigroup.cpp
        src/main/cpp/PFQuasigroup.h)
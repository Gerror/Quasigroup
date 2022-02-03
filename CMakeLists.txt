cmake_minimum_required(VERSION 3.16)
project(Quasigroup)

set(CMAKE_CXX_STANDARD 11)

add_executable(Quasigroup src/main/cpp/main.cpp
                          src/main/cpp/IncidenceCube.cpp
                          src/main/cpp/IncidenceCube.h
                          src/main/cpp/Quasigroup.cpp
                          src/main/cpp/Quasigroup.h)
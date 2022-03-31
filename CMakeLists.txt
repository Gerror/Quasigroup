cmake_minimum_required(VERSION 3.16)
project(Quasigroup)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        src/test/cpp
        src/main/cpp
        src/main/cpp/quasigroup
        src/main/cpp/quasigroup/functional
        src/main/cpp/quasigroup/latin_square
        src/main/cpp/function_family
)

add_executable(Quasigroup
        src/main/cpp/main.cpp
        src/main/cpp/IncidenceCube.cpp
        src/main/cpp/IncidenceCube.h
        src/test/cpp/tests.h
        src/test/cpp/tests.cpp
        src/main/cpp/quasigroup/Quasigroup.cpp
        src/main/cpp/quasigroup/Quasigroup.h
        src/main/cpp/Helper.cpp
        src/main/cpp/Helper.h
        src/main/cpp/GeneratedObject.cpp
        src/main/cpp/GeneratedObject.h
        src/main/cpp/quasigroup/latin_square/LatinSquareQuasigroup.cpp
        src/main/cpp/quasigroup/latin_square/LatinSquareQuasigroup.h
        src/main/cpp/quasigroup/latin_square/JMQuasigroup.cpp
        src/main/cpp/quasigroup/latin_square/JMQuasigroup.h
        src/main/cpp/function_family/FunctionFamily.cpp
        src/main/cpp/function_family/FunctionFamily.h
        src/main/cpp/function_family/ProperFamily.cpp
        src/main/cpp/function_family/ProperFamily.h
        src/main/cpp/quasigroup/functional/FunctionalQuasigroup.cpp
        src/main/cpp/quasigroup/functional/FunctionalQuasigroup.h
        src/main/cpp/quasigroup/functional/PFQuasigroup.cpp src/main/cpp/quasigroup/functional/PFQuasigroup.h)
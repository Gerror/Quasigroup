cmake_minimum_required(VERSION 3.16)
project(Quasigroup VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(QuasigroupLib
        src/main/cpp/utils/IncidenceCube.cpp
        src/main/cpp/quasigroup/Quasigroup.cpp
        src/main/cpp/utils/Helper.cpp
        src/main/cpp/generator/GeneratedObject.cpp
        src/main/cpp/quasigroup/square/LatinSquareQuasigroup.cpp
        src/main/cpp/quasigroup/square/JMQuasigroup.cpp
        src/main/cpp/function/family/FunctionFamily.cpp
        src/main/cpp/function/family/ProperFamily.cpp
        src/main/cpp/function/family/ShiftRegister.cpp
        src/main/cpp/quasigroup/functional/FunctionalQuasigroup.cpp
        src/main/cpp/quasigroup/functional/PFQuasigroup.cpp
        src/main/cpp/quasigroup/functional/SRQuasigroup.cpp
        src/main/cpp/function/family/FeistelNetwork.cpp
        src/main/cpp/quasigroup/functional/FNQuasigroup.cpp
        src/main/cpp/quasigroup/factory/JMQuasigroupFactory.cpp
        src/main/cpp/quasigroup/factory/SRQuasigroupFactory.cpp
        src/main/cpp/quasigroup/factory/FNQuasigroupFactory.cpp
        src/main/cpp/quasigroup/factory/PFQuasigroupFactory.cpp
        src/main/cpp/quasigroup/square/AffineQuasigroup.cpp
        src/main/cpp/quasigroup/factory/AffineQuasigroupFactory.cpp
        src/main/cpp/generator/QuasigroupGenerator.cpp
        src/main/cpp/quasigroup/group/AbelianGroup.cpp
        src/main/cpp/function/AbelianGroupAutomorphism.cpp
        src/main/cpp/statistics/experiment/QuantitiveExperiment.cpp
        src/main/cpp/statistics/experiment/GenerationTimeExperiment.cpp
        src/main/cpp/statistics/experiment/CheckPropertyTimeExperiment.cpp
        src/main/cpp/statistics/ExperimentalReport.cpp
        src/main/cpp/statistics/ExperimentsRunner.cpp
        src/main/cpp/quasigroup/group/DihedralGroup.cpp
        src/main/cpp/quasigroup/group/AlternatingGroup.cpp
        src/main/cpp/transformer/KepkaTransformer.cpp
        src/main/cpp/function/family/catalog/WellKnownProperFamilyCatalog.cpp
        src/main/cpp/transformer/PFQuasigroupPermutationTransformer.cpp
        src/main/cpp/quasigroup/functional/PFPermutatedQuasigroup.cpp
        src/main/cpp/quasigroup/factory/AbelianGroupFactory.cpp
        src/main/cpp/properties/CommutativeQuasigroupAssociativityByBasisResolver.cpp
        src/main/cpp/properties/SubquasigroupResolver.cpp
)

add_library(Quasigroup::QuasigroupLib ALIAS QuasigroupLib)

target_include_directories(QuasigroupLib PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/quasigroup>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/quasigroup/functional>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/quasigroup/square>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/quasigroup/factory>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/quasigroup/group>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/function>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/function/family>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/generator>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/statistics>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/statistics/experiment>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/transformer>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(QuasigroupLib PUBLIC cxx_std_17)

find_package(Threads REQUIRED)
target_link_libraries(QuasigroupLib PUBLIC Threads::Threads)

add_subdirectory(app)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS QuasigroupLib
        EXPORT QuasigroupTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY src/main/cpp/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.h"
)

install(EXPORT QuasigroupTargets
        FILE QuasigroupTargets.cmake
        NAMESPACE Quasigroup::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Quasigroup
)

configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/QuasigroupConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/QuasigroupConfig.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Quasigroup
)

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/QuasigroupConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/QuasigroupConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/QuasigroupConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Quasigroup
)
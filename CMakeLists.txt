cmake_minimum_required(VERSION 3.14)  # Rekomenduojama 3.14 dėl geresnio FetchContent palaikymo
project(objektinisProg2 LANGUAGES CXX)

# Nustatykite C++ standartą
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Aplankų kintamieji
set(SRC_DIR ${CMAKE_SOURCE_DIR}/Src)
set(INC_DIR ${CMAKE_SOURCE_DIR}/include)
set(BUILD_DIR ${CMAKE_SOURCE_DIR}/build)
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)
set(RESULTS_DIR ${CMAKE_SOURCE_DIR}/results)
set(TEST_FILES_DIR ${CMAKE_SOURCE_DIR}/test_files)
set(REZULTATAI_DIR ${CMAKE_SOURCE_DIR}/rezultatai)

# 1. Atsisiunčiame Catch2
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(Catch2)

# Pagrindinė biblioteka
add_library(CoreLib
    Src/versijos1Funkc.cpp
    Src/studentas.cpp
    Src/strategija3.cpp
    Src/LaikoMatavimas.cpp
    Src/testRuleOf5.cpp
)
target_include_directories(CoreLib PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)

# Pagrindinė programa
add_executable(main_program Src/v1.2.cpp)
target_link_libraries(main_program PRIVATE CoreLib)

# Testų programa
add_executable(tests Src/googleTests.cpp)


target_include_directories(tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${catch2_SOURCE_DIR}/extras  # catch_amalgamated.hpp vieta
)
target_link_libraries(tests PRIVATE 
    CoreLib 
    Catch2::Catch2WithMain
)

# Testų konfigūracija
enable_testing()
add_test(NAME ProjectTests COMMAND tests)

# Sukuriame atskirus aplankus su custom CMake target
add_custom_target(create_directories ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BUILD_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BIN_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${RESULTS_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${TEST_FILES_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${REZULTATAI_DIR}
)

# Sukuriame papildomą custom target, kad paleistume main programą arba testus
add_custom_target(run_main_program
    COMMAND main_program
    DEPENDS main_program
    WORKING_DIRECTORY ${BUILD_DIR}
)
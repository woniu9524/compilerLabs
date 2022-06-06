cmake_minimum_required(VERSION 3.17)
project(compileLabs C)

set(CMAKE_C_STANDARD 99)

add_executable(compileLabs main.c)
add_executable(lexicalAnalysis lexicalAnalysis.c)

add_executable(recursive-descent recursiveDescent.c)
add_executable(predictionAnalysis predictionAnalysis.c)
add_executable(calculator calculator.c)
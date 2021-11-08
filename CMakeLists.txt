cmake_minimum_required(VERSION 3.20)
project(Algorytmy2)

set(CMAKE_CXX_STANDARD 20)
add_executable(Algorytmy2 Source/main.cpp Source/LoadFromFile.cpp Header/LoadFromFile.h
        Header/BruteForce.h Source/BruteForce.cpp
        Source/RepresentationOfGraph/Matrix.cpp Header/RepresentationOfGraph/Matrix.h Source/DynamicProgramming.cpp Header/DynamicProgramming.h Source/B&B/BranchAndBound.cpp Header/B&B/BranchAndBound.h Source/B&B/Node.cpp Header/B&B/Node.h)

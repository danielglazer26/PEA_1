cmake_minimum_required(VERSION 3.20)
project(Algorytmy2)

set(CMAKE_CXX_STANDARD 20)
add_executable(Algorytmy2 Source/main.cpp Source/RepresentationOfGraph/LoadFromFile.cpp Header/RepresentationOfGraph/LoadFromFile.h
        Header/BF/BruteForce.h Source/BF/BruteForce.cpp
        Source/RepresentationOfGraph/Matrix.cpp Header/RepresentationOfGraph/Matrix.h Source/DP/DynamicProgramming.cpp Header/DP/DynamicProgramming.h Source/B&B/BranchAndBound.cpp Header/B&B/BranchAndBound.h Header/B&B/Node.h Header/DP/NodeDP.h)

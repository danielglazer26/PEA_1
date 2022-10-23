cmake_minimum_required(VERSION 3.20)
project(Algorytmy2)

set(CMAKE_CXX_STANDARD 20)
add_executable(Algorytmy
        Source/main.cpp
        Source/RepresentationOfGraph/LoadFromFile.cpp
        Header/RepresentationOfGraph/LoadFromFile.h
        Source/RepresentationOfGraph/Matrix.cpp
        Header/RepresentationOfGraph/Matrix.h
        Source/B&B/BranchAndBound.cpp
        Header/B&B/BranchAndBound.h
        Header/B&B/Node.h
        Header/B&B/BranchAndBoundThreads.h
        Source/B&B/BranchAndBoundThreads.cpp
        Source/B&B/ThreadPool.cpp Header/B&B/ThreadPool.h)

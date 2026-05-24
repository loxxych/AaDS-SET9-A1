cmake_minimum_required(VERSION 4.0)
project(SET9_A1)

set(CMAKE_CXX_STANDARD 20)

add_executable(SET9_A1 main.cpp
                StringGenerator/StringGenerator.h
                StringGenerator/StringGenerator.cpp
                StringSortTester/StringSortTester.cpp
                StringSortTester/StringSortTester.h
                StringSort/MergeSort/MergeSorter.cpp
                StringSort/MergeSort/MergeSorter.h
                StringSort/QuickSort/QuickSorter.cpp
                StringSort/QuickSort/QuickSorter.h
                StringSort/RadixSort/RadixSorter.cpp
                StringSort/RadixSort/RadixSorter.h)

add_executable(A1m CodeforcesTasks/A1m.cpp)

add_executable(A1q CodeforcesTasks/A1q.cpp)

add_executable(A1r CodeforcesTasks/A1r.cpp)

add_executable(A1rq CodeforcesTasks/A1rq.cpp)

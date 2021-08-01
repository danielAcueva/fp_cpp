Functional Programming (FP) C++ (CPP) Demonstration
===================================================

Overview:
---------
This software source code is for demonstation and leanring purposes only. This 
software is not used as production software or a library extension. This software 
is intended to study and apply concepts in and C++ software implementation. The
concepts explored here can easily be applied to any application where FP makes
sense.

FP Concepts Demonstrated:
-------------------------
    * List Recursion
        - Including tail recursion
    * High Order Functions (HOFs)
        - Including Haskell map and foldr equivalents
    * Algebraic Data Types
        - Sum types
    * Pattern Matching
    * Curried Functions
    * Lazy Evaluation
    * Monads
        - Haskell maybe monad equivalent

Components:
-----------
This software package consists of four components:
    * fp_cpp.h
        - C++ implementation of FP concepts 
        - Example demonstrative functions to prove FP concepts
    * fp_test.cpp
        - C++ test code to exercise the FP examples in fp_cpp.h
        - Comprehensive tests which prove the functionality of the FP concepts
    * build_fp_cpp.sh
        - Shell script to build test code
        - The resulting executable (fp_cpp) can be executed to verify functionality
    * README.txt
        - This file
        - Overview of the software package and software components
        - Instructions for building and running software

Build/Execute Instructions:
---------------------------
Building and Running Instructions
    * Ensure g++ 8 or higher is installed for C++ 2a
    * Execute the shell script to build the software
        - `/bin/sh build_fp_cpp.sh`
        - If executed correctly, an executable will be produced (fp_cpp)
    * Execute the software
        - `./fp_cpp`
        - This will run the comprehensive tests
    * View test results and examine code
        - To understand the code, examine test and source code

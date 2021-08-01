#!/bin/bash

# Remove old program executable
rm -rf fp_cpp

# Compile the program
g++-8 -std=gnu++2a -o fp_cpp fp_test.cpp

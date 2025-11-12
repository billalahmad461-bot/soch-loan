#!/bin/bash

# Create bin folder if it doesn't exist
mkdir -p bin

# Compile main.cpp (root) and other cpp files in src/, headers in include/
g++ main.cpp src/utterence-handler.cpp src/loan-selection.cpp -Iinclude -o bin/program

# Run if compilation succeeded
if [ $? -eq 0 ]; then
    echo "Compilation successful!"
    ./bin/program
else
    echo "Compilation failed."
fi

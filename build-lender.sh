#!/bin/bash

mkdir -p bin

sources="lender.cpp"
for file in src/*.cpp; do
    sources="$sources $file"
done

g++ $sources -Iinclude -o bin/lender

if [ $? -eq 0 ]; then
    echo "Compilation successful!"
    ./bin/lender
else
    echo "Compilation failed."
fi

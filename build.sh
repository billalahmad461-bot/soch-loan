#!/bin/bash

# Create bin folder if it doesn't exist
mkdir -p bin

# Gather all cpp files: soch-bot.cpp + all src/*.cpp
sources="soch-bot.cpp"
for file in src/*.cpp; do
    sources="$sources $file"
done

# Compile all source files
g++ $sources -Iinclude -o bin/soch-bot

# Run if compilation succeeded
if [ $? -eq 0 ]; then
    echo "Compilation successful!"
    ./bin/soch-bot
else
    echo "Compilation failed."
fi

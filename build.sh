#!/bin/bash

# Check if the current directory has a CMakeLists.txt
if [ ! -f CMakeLists.txt ]; then
    echo "Error: No CMakeLists.txt found in the current directory."
    exit 1
fi

# Create build directory if it doesn't exist
if [ ! -d buildYaya ]; then
    mkdir buildYaya
else
    rm -rf buildYaya
    echo "Removed build"
    mkdir buildYaya
fi

# Change to the build directory
cd buildYaya

# Run cmake
cmake ..

# Run make (or ninja, or whatever build tool you've set up with CMake)
make
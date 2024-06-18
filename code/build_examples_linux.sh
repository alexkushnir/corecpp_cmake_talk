#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <base-examples-directory>"
    exit 1
fi

BASE_DIR=$1

directories=($(find $BASE_DIR -maxdepth 1 -mindepth 1 -type d | grep -v "modules"))

# Iterate over the array and print each directory name
for dir in "${directories[@]}"; 
do
    echo "Configuring the $dir example"
    cmake -GNinja -S $dir -B $dir-build
    echo "Building the $dir example"
    cmake --build $dir-build
done

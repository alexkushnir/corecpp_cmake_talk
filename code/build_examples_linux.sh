#!/bin/bash
# declare -A EXAMPLE_FOLDERS=("01-basic-example" "02-find_package" "03-fetch-content") # 04-cpp-modules is not for Linux 

# printf "%s" "${EXAMPLE_FOLDERS[@]}"
# for dir in "${EXAMPLE_FOLDERS[@]}"
# do
#    echo "$dir"
#     echo "Configuring the $dir example"
#     cmake -GNinja -S $dir -B $dir-build
#     echo "Building the $dir example"
#     cmake --build $dir-build
# done

#!/bin/bash

# Store directory names in an array
directories=($(find . -maxdepth 1 -type d ! -name . | grep -v "modules"))

# Iterate over the array and print each directory name
for dir in "${directories[@]}"; 
do

    # echo $dir
    echo "Configuring the $dir example"
    cmake -GNinja -S $dir -B $dir-build
    echo "Building the $dir example"
    cmake --build $dir-build
done

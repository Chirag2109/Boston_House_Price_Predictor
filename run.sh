#!/bin/bash

# Function to check if a library is installed
check_library() {
    ldconfig -p | grep "$1" > /dev/null
    return $?
}

# Check for GSL, GSL CBLAS, and math libraries
echo "Checking for required libraries..."

if check_library "libgsl.so"; then
    echo "GSL library is present."
else
    echo "GSL library is not found. Installing..."
    sudo apt-get update
    sudo apt-get install -y libgsl-dev
fi

if check_library "libgslcblas.so"; then
    echo "GSL CBLAS library is present."
else
    echo "GSL CBLAS library is not found. Installing..."
    sudo apt-get update
    sudo apt-get install -y libgsl-dev
fi

if check_library "libgcc_s.so"; then
    echo "GCC library is present."
else
    echo "GCC library is not found. Installing..."
    sudo apt-get update
    sudo apt-get install -y build-essential
fi

cd Temporary_Files

gcc -c ../Libraries/statistics.c -o statistics.o
gcc -c ../Libraries/sklearn.c -o sklearn.o
gcc -c ../Libraries/io_control.c -o io_control.o

ar rcs mylib.a io_control.o sklearn.o statistics.o

# Compile the C program with the necessary libraries
gcc -c ../Libraries/Boston_Dataset_Analysis.c -o Boston_Dataset_Analysis.o -L. -l:mylib.a -lgsl -lgslcblas -lm

ar rcs model.a Boston_Dataset_Analysis.o

gcc -o output ../output.c -L. model.a mylib.a -lgsl -lgslcblas -lm

# Run the compiled program
./output

# Remove the object files
rm -f *.o

# Remove the static library
rm -f *.a

# Remove the executable
rm -f output

#!/bin/bash

# Stop the script if any command fails
set -e
trap 'echo "Error on line $LINENO: $BASH_COMMAND"; exit 1;' ERR

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

# Compile the libraries
gcc -c ../Libraries/metrics.c -o metrics.o
gcc -c ../Libraries/statistics.c -o statistics.o
gcc -c ../Libraries/io_control.c -o io_control.o
gcc -c ../Libraries/linear_regression.c -o linear_regression.o

ar rcs mylib.a metrics.o io_control.o statistics.o linear_regression.o
gcc -c ../Libraries/model.c -o model.o -L. -l:mylib.a -lgsl -lgslcblas -lm


ar rcs model.a model.o
gcc -o Main ../Main.c -L. model.a mylib.a -lgsl -lgslcblas -lm

# Run the compiled program
./output

# Clean up
rm -f *.o
rm -f *.a
rm -f Main

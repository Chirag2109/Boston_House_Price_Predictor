#!/bin/bash

cd Temporary_Files

gcc -c ../Libraries/metrics.c -o metrics.o
gcc -c ../Libraries/statistics.c -o statistics.o
gcc -c ../Libraries/io_control.c -o io_control.o
gcc -c ../Libraries/linear_regression.c -o linear_regression.o

ar rcs mylib.a metrics.o io_control.o statistics.o linear_regression.o

# Compile the C program with the inbuilt and custom libraries
gcc -c ../Libraries/Boston_Dataset_Analysis.c -o Boston_Dataset_Analysis.o -L. -l:mylib.a -lgsl -lgslcblas -lm

ar rcs model.a Boston_Dataset_Analysis.o

gcc -o output ../output.c -L. model.a mylib.a -lgsl -lgslcblas -lm

# Run the compiled program
./output

# Remove the temporary files in the Temporary_Files folder
rm -f *.o
rm -f *.a
rm -f output

# Developer's Documentation

This is a guide for assisting in the further development of this toolbox.
The purpose of various functions and files has been explained.
Various useful and/or important techniques have also been explained.

## builder.sce

This file serves as the makefile for the toolbox. It contains a list of:

1. The names of the functions that the toolbox will make available in Scilab
2. The corresponding names of the functions in the toolbox source code
3. A list of source files to be compiled
4. Various compiler and linker flags

The linker flags may have to be changed if Symphony has been installed from source.

## sci_iofunc.hpp

This header file contains various functions for obtaining arguments for functions from Scilab and returning data back to Scilab.
The following functions are available (The names should be self explanatory):

1. `int getDoubleFromScilab(int argNum, double *dest);`
2. `int getUIntFromScilab(int argNum, int *dest);`
3. `int getIntFromScilab(int argNum, int *dest);`
4. `int getFixedSizeDoubleMatrixFromScilab(int argNum, int rows, int cols, double **dest);`
5. `int getDoubleMatrixFromScilab(int argNum, int *rows, int *cols, double **dest);`
6. `int return0toScilab();`
7. `int returnDoubleToScilab(double retVal);`

Anything that is not a pointer is data that is to be passed to the function.
Anything that is a pointer is the destination for data that will be returned by the function.
All functions return 0 if no errors occur and 1 if any error occurs.

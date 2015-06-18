# Developer's Documentation

This is a guide for assisting in the further development of this toolbox.
The purpose of various functions and files has been explained.
Various useful and/or important techniques have also been explained.
**It is recommended that you read this file completely.**

## `builder.sce`

This file serves as the makefile for the toolbox. It contains a list of:

1. The names of the functions that the toolbox will make available in Scilab
2. The corresponding names of the functions in the toolbox source code
3. A list of source files to be compiled
4. Various compiler and linker flags

The linker flags may have to be changed if Symphony has been installed from source.

## `sci_iofunc.hpp`

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

## `template.cpp`

This file serves as a template for any C++ source file to be created.
The function name `sci_template` should be replaced by the actual function name, and all relevant blanks should be filled out.
Multiple functions can be placed in the same source file, within the `extern "C"` braces, but only do so if they have similar functionality.

## `sym_testscript.sce`

This is a large script file that runs multiple tests on the toolbox at once. If you create any new functions, please add them to the appropriate section of the test script.

## Sparse matrix representation formats

Scilab and Symphony use different methods of representing sparse matrices.
**Suppose a matrix has n rows, m columns, and nz nonzero items**
Scilab will provide (and expect) sparse matrix data in the following form:

1. Number of non-zero values in the matrix
2. Array of size n specifying the number of items in each row
3. Array of size nz specifying the column index of each item
4. Array of size nz containing the actual items

Symphony, however, requires the following format:

1. Array of size nz containing the actual items
2. Array of size nz specifying the row index of each item
3. Array of size **m+1** specifying the starting positions of each column in the items array, including a final entry for the last nonexistant column. This last entry should be equal to nz

An algorithm for converting from the Scilab format to the Symphony format is present in the `sci_sym_loadProblem` function in the file `sci_sym_loadproblem.cpp`. An algorithm for the reverse process is present in the `column_major_to_row_major` function in the file `sym_data_query_functions.cpp`.

## Additional help

Additional help can be obtained from the 'API Scilab' section of the Scilab user documentation. It details the functions available for getting data from Scilab and returning data back to it.

// Symphony Toolbox for Scilab
// (Declaration of) Functions for input and output from Scilab
// By Keyur Joshi

#ifndef SCI_IOFUNCHEADER
#define SCI_IOFUNCHEADER

//input
extern int getDoubleFromScilab(int argNum, double *dest);
extern int getUIntFromScilab(int argNum, int *dest);

//output
extern int return0toScilab();

#endif //SCI_IOFUNCHEADER

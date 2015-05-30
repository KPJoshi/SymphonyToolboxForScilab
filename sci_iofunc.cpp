// Symphony Toolbox for Scilab
// (Definition of) Functions for input and output from Scilab
// By Keyur Joshi

#include "api_scilab.h"
#include "Scierror.h"
#include "sciprint.h"
#include "BOOL.h"
#include <localization.h>

int getDoubleFromScilab(int argNum, double *dest)
{
	//data declarations
	SciErr sciErr;
	int iRet,*varAddress;
	const char errMsg[]="Wrong type for input argument #%d: A double is expected.\n";
	const int errNum=999;
	//get variable address
	sciErr = getVarAddressFromPosition(pvApiCtx, argNum, &varAddress);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		return 1;
	}
	//check that it is a non-complex double
	if ( !isDoubleType(pvApiCtx,varAddress) ||  isVarComplex(pvApiCtx,varAddress) )
	{
		Scierror(errNum,errMsg,argNum);
		return 1;
	}
	//retrieve and store
	iRet = getScalarDouble(pvApiCtx, varAddress, dest);
	if(iRet)
	{
		Scierror(errNum,errMsg,argNum);
		return 1;
	}
	return 0;
}

int getUIntFromScilab(int argNum, int *dest)
{
	SciErr sciErr;
	int iRet,*varAddress;
	double inputDouble;
	const char errMsg[]="Wrong type for input argument #%d: A nonnegative integer is expected.\n";
	const int errNum=999;
	sciErr = getVarAddressFromPosition(pvApiCtx, argNum, &varAddress);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		return 1;
	}
	if ( !isDoubleType(pvApiCtx,varAddress) ||  isVarComplex(pvApiCtx,varAddress) )
	{
		Scierror(errNum,errMsg,argNum);
		return 1;
	}
	iRet = getScalarDouble(pvApiCtx, varAddress, &inputDouble);
	if(iRet || ((double)((unsigned int)inputDouble))!=inputDouble)
	{
		Scierror(errNum,errMsg,argNum);
		return 1;
	}
	*dest=(unsigned int)inputDouble;
	return 0;
}

int return0toScilab()
{
	int iRet;
	iRet = createScalarDouble(pvApiCtx, nbInputArgument(pvApiCtx)+1,0);
	if(iRet)
	{
		/* If error, no return variable */
		AssignOutputVariable(pvApiCtx, 1) = 0;
		return 1;
	}
	AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx)+1;
	ReturnArguments(pvApiCtx);
	return 0;
}

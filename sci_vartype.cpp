/*
 * Symphony Toolbox
 * Provides information about variables: is it continuous/integer/boolean?
 * By Keyur Joshi
 * Last edit 25-5-15
 */

#include "symphony.h"

extern sym_environment* global_sym_env; //defined in globals.cpp

extern "C" {
#include "api_scilab.h"
#include "Scierror.h"
#include "sciprint.h"
#include "BOOL.h"
#include <localization.h>

//error management variable
static SciErr sciErr;
static int iRet;

//data declarations
static int *varAddress,varIndex,retVal;
static double inputDouble;

static int commonCodePart1(){
	//ensure that environment is active
	if(global_sym_env==NULL){
		sciprint("Error: Symphony environment not initialized. Please run 'sym_open()' first.\n");
		return 1;
	}
	
	//code to check arguments and get them
	CheckInputArgument(pvApiCtx,1,1) ;
	CheckOutputArgument(pvApiCtx,1,1) ;
	
	//code to process input
	sciErr = getVarAddressFromPosition(pvApiCtx, 1, &varAddress);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		return 1;
	}
	if ( !isDoubleType(pvApiCtx,varAddress) ||  isVarComplex(pvApiCtx,varAddress) )
	{
		Scierror(999, "Wrong type for input argument #1: A positive integer stored in a double is expected.\n");
		return 1;
	}
	iRet = getScalarDouble(pvApiCtx, varAddress, &inputDouble);
	if(iRet || ((double)((unsigned int)inputDouble))!=inputDouble)
	{
		Scierror(999, "Wrong type for input argument #1: A positive integer stored in a double is expected.\n");
		return 1;
	}
	varIndex=((unsigned int)inputDouble)-1;
	
	return 0;
}

static int commonCodePart2(){
	//code to give output
	iRet = createScalarDouble(pvApiCtx, nbInputArgument(pvApiCtx)+1, (double)retVal);
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

int sci_sym_isContinuous(char *fname){
	
	if(commonCodePart1())
		return 1;
	
	iRet=sym_is_continuous(global_sym_env,varIndex,&retVal);
	if(iRet==FUNCTION_TERMINATED_ABNORMALLY){
		Scierror(999, "An error occured. Has a problem been loaded?\n");
		return 1;
	}else{
		if(retVal)
			sciprint("This variable is continuous.\n");
		else
			sciprint("This variable is not continuous.\n");
	}
	
	if(commonCodePart2())
		return 1;
	
	return 0;
}

int sci_sym_isBinary(char *fname){
	
	if(commonCodePart1())
		return 1;

	iRet=sym_is_binary(global_sym_env,varIndex,&retVal);
	if(iRet==FUNCTION_TERMINATED_ABNORMALLY){
		Scierror(999, "An error occured.\n");
		return 1;
	}else{
		if(retVal)
			sciprint("This variable is constrained to be binary.\n");
		else
			sciprint("This variable is not constrained to be binary.\n");
	}
	
	if(commonCodePart2())
		return 1;
	
	return 0;
}

int sci_sym_isInteger(char *fname){
	
	char retVal; //for some wierd reason this function unlike the above 2 returns a char
	
	if(commonCodePart1())
		return 1;
	
	iRet=sym_is_integer(global_sym_env,varIndex,&retVal);
	if(iRet==FUNCTION_TERMINATED_ABNORMALLY){
		Scierror(999, "An error occured.\n");
		return 1;
	}else{
		if(retVal)
			sciprint("This variable is constrained to be an integer.\n");
		else
			sciprint("This variable is not constrained to be an integer.\n");
	}
	
	if(commonCodePart2())
		return 1;
	
	return 0;
}

}

/*
 * Symphony Toolbox
 * Functions for setting the coefficients of the objective and the sense (minimization/maximization)
 * By Keyur Joshi
 */

#include "symphony.h"

extern sym_environment* global_sym_env; //defined in globals.cpp

extern "C" {
#include "api_scilab.h"
#include "Scierror.h"
#include "sciprint.h"
#include "BOOL.h"
#include <localization.h>

int sci_sym_setObjCoeff(char *fname){
	
	//error management variable
	SciErr sciErr;
	int iRet;
	
	//data declarations
	int *varAddress,varIndex,numVars;
	double inputDouble,newCoeff;
	
	//ensure that environment is active
	if(global_sym_env==NULL){
		sciprint("Error: Symphony environment not initialized. Please run 'sym_open()' first.\n");
		return 1;
	}
	
	//code to check arguments and get them
	CheckInputArgument(pvApiCtx,2,2) ;
	CheckOutputArgument(pvApiCtx,1,1) ;
	
	//get argument 1: index of variable whose coefficient is to be changed
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
	varIndex=(unsigned int)inputDouble;
	iRet=sym_get_num_cols(global_sym_env,&numVars);
	if(iRet==FUNCTION_TERMINATED_ABNORMALLY){
		Scierror(999, "An error occured. Has a problem been loaded?\n");
		return 1;
	}else if(varIndex>=numVars){
		Scierror(999, "An error occured. Variable index must be a number between 0 and %d.\n",numVars-1);
		return 1;
	}
	
	//get argument 2: new coefficient
	sciErr = getVarAddressFromPosition(pvApiCtx, 2, &varAddress);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		return 1;
	}
	if ( !isDoubleType(pvApiCtx,varAddress) ||  isVarComplex(pvApiCtx,varAddress) )
	{
		Scierror(999, "Wrong type for input argument #1: A double is expected.\n");
		return 1;
	}
	iRet = getScalarDouble(pvApiCtx, varAddress, &newCoeff);
	if(iRet)
	{
		Scierror(999, "Wrong type for input argument #1: A double is expected.\n");
		return 1;
	}
	
	iRet=sym_set_obj_coeff(global_sym_env,varIndex,newCoeff);
	if(iRet==FUNCTION_TERMINATED_ABNORMALLY){
		Scierror(999, "An error occured. Has a problem been loaded?\n");
		return 1;
	}else{
		sciprint("Coefficient successfully changed.\n");
	}
	
	//code to give output
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

int sci_sym_setObjSense(char *fname){
	
	//error management variable
	SciErr sciErr;
	int iRet;
	
	//data declarations
	int *varAddress;
	double objSense;
	
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
		Scierror(999, "Wrong type for input argument #1: Either 1 or -1 is expected.\n");
		return 1;
	}
	iRet = getScalarDouble(pvApiCtx, varAddress, &objSense);
	if(iRet || (objSense!=-1 && objSense!=1))
	{
		Scierror(999, "Wrong type for input argument #1: Either 1 or -1 is expected.\n");
		return 1;
	}
	iRet=sym_set_obj_sense(global_sym_env,objSense);
	if(iRet==FUNCTION_TERMINATED_ABNORMALLY){
		Scierror(999, "An error occured.\n");
		return 1;
	}else{
		if(objSense==1)
			sciprint("The solver has been set to minimize the objective.\n");
		else
			sciprint("The solver has been set to maximize the objective.\n");
	}
	
	//code to give output
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

}

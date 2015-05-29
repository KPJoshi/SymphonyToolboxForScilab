/*
 * Symphony Toolbox
 * Functions to add a new row or column
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

int sci_sym_addConstr(char *fname){
	
	//error management variable
	SciErr sciErr;
	int iRet;
	
	//data declarations
	int *varAddress,numVars,nonZeros,*itemsPerRow,*colIndex,inputRows,inputCols;
	double inputDouble,*matrix,conRHS,conRHS2,conRange;
	char conType,*conTypeInput;
	bool isRangedConstr=false;
	
	//ensure that environment is active
	if(global_sym_env==NULL){
		sciprint("Error: Symphony environment not initialized. Please run 'sym_open()' first.\n");
		return 1;
	}
	
	//code to check arguments and get them
	CheckInputArgument(pvApiCtx,3,4) ;
	CheckOutputArgument(pvApiCtx,1,1) ;
	
	//get number of columns
	iRet=sym_get_num_cols(global_sym_env,&numVars);
	if(iRet==FUNCTION_TERMINATED_ABNORMALLY){
		Scierror(999, "An error occured. Has a problem been loaded?\n");
		return 1;
	}
	
	//get input 1: sparse matrix of variable coefficients in new constraint
	sciErr = getVarAddressFromPosition(pvApiCtx, 1, &varAddress);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		return 1;
	}
	if ( !isSparseType(pvApiCtx,varAddress) ||  isVarComplex(pvApiCtx,varAddress) )
	{
		Scierror(999, "Wrong type for input argument #1: A sparse matrix of doubles is expected.\n");
		return 1;
	}
	sciErr = getSparseMatrix(pvApiCtx,varAddress,&inputRows,&inputCols,&nonZeros,&itemsPerRow,&colIndex,&matrix);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		return 1;
	}
	if(inputRows!=1 || inputCols!=numVars)
	{
		Scierror(999, "Wrong type for input argument #1: Incorrectly sized matrix.\n");
		return 1;
	}
	
	//get argument 2: type of constraint
	sciErr = getVarAddressFromPosition(pvApiCtx, 2, &varAddress);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		return 1;
	}
	if ( !isStringType(pvApiCtx,varAddress) )
	{
		Scierror(999, "Wrong type for input argument #2: Either \"L\", \"E\", \"G\", or \"R\" is expected.\n");
		return 1;
	}
	iRet = getAllocatedSingleString(pvApiCtx, varAddress, &conTypeInput);
	if(iRet)
	{
		Scierror(999, "Wrong type for input argument #2: Either \"L\", \"E\", \"G\", or \"R\" is expected.\n");
		return 1;
	}
	switch(conTypeInput[0]){
		case 'l':case 'L':
			conType='L';
			break;
		case 'e':case 'E':
			conType='E';
			break;
		case 'g':case 'G':
			conType='G';
			break;
		case 'r':case 'R':
			conType='R';
			isRangedConstr=true;
			break;
		default:
			Scierror(999, "Wrong type for input argument #2: Either \"L\", \"E\", \"G\", or \"R\" is expected.\n");
			return 1;
	}
	//check number of arguments for specific cases
	if(isRangedConstr){
		if(nbInputArgument(pvApiCtx)!=4){
			Scierror(999, "4 Arguments are expected for ranged constraint.\n");
			return 1;
		}
	}else if(nbInputArgument(pvApiCtx)!=3){
		Scierror(999, "3 Arguments are expected for non-ranged constraint.\n");
		return 1;
	}
	
	//get argument 3: constraint RHS
	sciErr = getVarAddressFromPosition(pvApiCtx, 3, &varAddress);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		return 1;
	}
	if ( !isDoubleType(pvApiCtx,varAddress) ||  isVarComplex(pvApiCtx,varAddress) )
	{
		Scierror(999, "Wrong type for input argument #3: A double is expected.\n");
		return 1;
	}
	iRet = getScalarDouble(pvApiCtx, varAddress, &conRHS);
	if(iRet)
	{
		Scierror(999, "Wrong type for input argument #3: A double is expected.\n");
		return 1;
	}
	
	//get argument 4: constraint range
	if(isRangedConstr){
		sciErr = getVarAddressFromPosition(pvApiCtx, 4, &varAddress);
		if (sciErr.iErr)
		{
			printError(&sciErr, 0);
			return 1;
		}
		if ( !isDoubleType(pvApiCtx,varAddress) ||  isVarComplex(pvApiCtx,varAddress) )
		{
			Scierror(999, "Wrong type for input argument #4: A double is expected.\n");
			return 1;
		}
		iRet = getScalarDouble(pvApiCtx, varAddress, &conRHS2);
		if(iRet)
		{
			Scierror(999, "Wrong type for input argument #4: A double is expected.\n");
			return 1;
		}
		//conRHS should be the upper bound, and conRange should be positive
		if(conRHS>=conRHS2){
			conRange=conRHS-conRHS2;
		}else{
			conRange=conRHS2-conRHS;
			conRHS=conRHS2;
		}
	}else{
		//if not ranged constraint, just set it to 0, the value probably does not matter anyway
		conRange=0;
	}
	
	iRet=sym_add_row(global_sym_env,nonZeros,colIndex,matrix,conType,conRHS,conRange);
	if(iRet==FUNCTION_TERMINATED_ABNORMALLY){
		Scierror(999, "An error occured.\n");
		return 1;
	}else{
		sciprint("Constraint successfully added.\n");
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

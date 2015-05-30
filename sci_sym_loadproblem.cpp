/*
 * Symphony Toolbox
 * Explicit problem loaders
 * Made by Keyur Joshi
 */
#include "symphony.h"
#include "sci_iofunc.hpp"

extern sym_environment* global_sym_env; //defined in globals.cpp

extern "C" {
#include "api_scilab.h"
#include "Scierror.h"
#include "sciprint.h"
#include "BOOL.h"
#include <localization.h>

//error management variables
static SciErr sciErr;
static int iRet;

//data declarations
static int *varAddress=NULL,numVars,numConstr,*conMatrixColStart=NULL,*conMatrixRowIndex=NULL,*isIntVarBool=NULL,*conTypeInputLen=NULL,colIter,rowIter,inputMatrixCols,inputMatrixRows;
static double inputDouble,*objective=NULL,*lowerBounds=NULL,*upperBounds=NULL,*conRHS=NULL,*conRange=NULL,*conVals=NULL;
static char *conType=NULL,*isIntVar=NULL,**conTypeInput=NULL;

//delete all allocd arrays before exit, and return output argument
static void cleanupBeforeExit(){
	if(conMatrixColStart) delete[] conMatrixColStart;
	if(conMatrixRowIndex) delete[] conMatrixRowIndex;
	if(isIntVar) delete[] isIntVar;
	if(conTypeInputLen) delete[] conTypeInputLen;
	for(rowIter=0;rowIter<numConstr;rowIter++)
		delete[] conTypeInput[rowIter];
	delete[] conTypeInput;
	if(conType) delete[] conType;
	ReturnArguments(pvApiCtx);
}

//both basic and advanced loader use this code
static int commonCodePart1(){
	
	//ensure that environment is active
	if(global_sym_env==NULL){
		sciprint("Error: Symphony environment not initialized. Please run 'sym_open()' first.\n");
		return 1;
	}
	
	//code to check arguments and get them
	CheckInputArgument(pvApiCtx,9,9);
	CheckOutputArgument(pvApiCtx,1,1);
	
	//get input 1: number of variables
	if(getUIntFromScilab(1,&numVars))
		return 1;
	
	//get input 2: number of constraints
	if(getUIntFromScilab(2,&numConstr))
		return 1;
	
	//allocate and prepare some arrays
	isIntVar=new char[numVars]; //is the variable constrained to be an integer?
	conTypeInputLen=new int[numConstr]; //length of string input for constraint type
	conTypeInput=new char*[numConstr]; //string input for constraint type
	conType=new char[numConstr]; //char representing constraint type
	for(rowIter=0;rowIter<numConstr;rowIter++)
		conTypeInput[rowIter]=new char[2];

	return 0;
}

//both basic and advanced loader use this code
static int commonCodePart2(){
	//get input 3: lower bounds of variables
	sciErr = getVarAddressFromPosition(pvApiCtx, 3, &varAddress);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		cleanupBeforeExit();return 1;
	}
	if ( !isDoubleType(pvApiCtx,varAddress) ||  isVarComplex(pvApiCtx,varAddress) )
	{
		Scierror(999, "Wrong type for input argument #3: A matrix of doubles is expected.\n");
		cleanupBeforeExit();return 1;
	}
	sciErr = getMatrixOfDouble(pvApiCtx, varAddress, &inputMatrixRows, &inputMatrixCols, &lowerBounds);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		cleanupBeforeExit();return 1;
	}
	if(inputMatrixRows!=1 || inputMatrixCols!=numVars)
	{
		Scierror(999, "Wrong type for input argument #3: Incorrectly sized matrix.\n");
		cleanupBeforeExit();return 1;
	}
	
	//get input 4: upper bounds of variables
	sciErr = getVarAddressFromPosition(pvApiCtx, 4, &varAddress);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		cleanupBeforeExit();return 1;
	}
	if ( !isDoubleType(pvApiCtx,varAddress) ||  isVarComplex(pvApiCtx,varAddress) )
	{
		Scierror(999, "Wrong type for input argument #4: A matrix of doubles is expected.\n");
		cleanupBeforeExit();return 1;
	}
	sciErr = getMatrixOfDouble(pvApiCtx, varAddress, &inputMatrixRows, &inputMatrixCols, &upperBounds);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		cleanupBeforeExit();return 1;
	}
	if(inputMatrixRows!=1 || inputMatrixCols!=numVars)
	{
		Scierror(999, "Wrong type for input argument #4: Incorrectly sized matrix.\n");
		cleanupBeforeExit();return 1;
	}
	
	//get input 5: coefficients of variables in objective function to be minimized
	sciErr = getVarAddressFromPosition(pvApiCtx, 5, &varAddress);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		cleanupBeforeExit();return 1;
	}
	if ( !isDoubleType(pvApiCtx,varAddress) ||  isVarComplex(pvApiCtx,varAddress) )
	{
		Scierror(999, "Wrong type for input argument #5: A matrix of doubles is expected.\n");
		cleanupBeforeExit();return 1;
	}
	sciErr = getMatrixOfDouble(pvApiCtx, varAddress, &inputMatrixRows, &inputMatrixCols, &objective);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		cleanupBeforeExit();return 1;
	}
	if(inputMatrixRows!=1 || inputMatrixCols!=numVars)
	{
		Scierror(999, "Wrong type for input argument #5: Incorrectly sized matrix.\n");
		cleanupBeforeExit();return 1;
	}
	
	//get input 6: array that specifies wether a variable is constrained to be an integer
	sciErr = getVarAddressFromPosition(pvApiCtx, 6, &varAddress);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		cleanupBeforeExit();return 1;
	}
	if ( !isBooleanType(pvApiCtx, varAddress) )
	{
		Scierror(999, "Wrong type for input argument #6: A matrix of booleans is expected.\n");
		cleanupBeforeExit();return 1;
	}
	sciErr = getMatrixOfBoolean(pvApiCtx, varAddress, &inputMatrixRows, &inputMatrixCols, &isIntVarBool);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		cleanupBeforeExit();return 1;
	}
	if(inputMatrixRows!=1 || inputMatrixCols!=numVars)
	{
		Scierror(999, "Wrong type for input argument #6: Incorrectly sized matrix.\n");
		cleanupBeforeExit();return 1;
	}
	for(colIter=0;colIter<numVars;colIter++)
	{
		if(isIntVarBool[colIter])
			isIntVar[colIter]=TRUE;
		else
			isIntVar[colIter]=FALSE;
	}
	
	//get input 8: constraint type (less than/equal to/more than)
	sciErr = getVarAddressFromPosition(pvApiCtx, 8, &varAddress);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		cleanupBeforeExit();return 1;
	}
	if ( !isStringType(pvApiCtx,varAddress) )
	{
		Scierror(999, "Wrong type for input argument #8: A matrix of strings is expected.\n");
		cleanupBeforeExit();return 1;
	}
	sciErr = getMatrixOfString(pvApiCtx, varAddress, &inputMatrixRows, &inputMatrixCols, NULL, NULL);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		cleanupBeforeExit();return 1;
	}
	if(inputMatrixRows!=numConstr || inputMatrixCols!=1)
	{
		Scierror(999, "Wrong type for input argument #8: Incorrectly sized matrix.\n");
		cleanupBeforeExit();return 1;
	}
	getMatrixOfString(pvApiCtx, varAddress, &inputMatrixRows, &inputMatrixCols, conTypeInputLen, NULL);
	for(rowIter=0;rowIter<numConstr;rowIter++)
		if(conTypeInputLen[rowIter]!=1)
		{
			Scierror(999, "Wrong type for input argument #8: Each string in matrix must be of length 1\n");
			cleanupBeforeExit();return 1;
		}
	getMatrixOfString(pvApiCtx, varAddress, &inputMatrixRows, &inputMatrixCols, conTypeInputLen, conTypeInput);
	for(rowIter=0;rowIter<numConstr;rowIter++)
	{
		switch(conTypeInput[rowIter][0])
		{
			case 'L':case 'l':
				conType[rowIter]='L';
				break;
			case 'E':case 'e':
				conType[rowIter]='E';
				break;
			case 'G':case 'g':
				conType[rowIter]='G';
				break;
			default:
				Scierror(999, "Wrong type for input argument #8: Unrecognized character. Only 'L', 'E', 'G' are allowed.\n");
				cleanupBeforeExit();return 1;
		}
	}
	
	//get input 9: constraint RHS
	sciErr = getVarAddressFromPosition(pvApiCtx, 9, &varAddress);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		cleanupBeforeExit();return 1;
	}
	if ( !isDoubleType(pvApiCtx,varAddress) ||  isVarComplex(pvApiCtx,varAddress) )
	{
		Scierror(999, "Wrong type for input argument #9: A matrix of doubles is expected.\n");
		cleanupBeforeExit();return 1;
	}
	sciErr = getMatrixOfDouble(pvApiCtx, varAddress, &inputMatrixRows, &inputMatrixCols, &conRHS);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		cleanupBeforeExit();return 1;
	}
	if(inputMatrixRows!=numConstr || inputMatrixCols!=1)
	{
		Scierror(999, "Wrong type for input argument #9: Incorrectly sized matrix.\n");
		cleanupBeforeExit();return 1;
	}
	
	//call problem loader
	sym_explicit_load_problem(global_sym_env,numVars,numConstr,conMatrixColStart,conMatrixRowIndex,conVals,lowerBounds,upperBounds,isIntVar,objective,NULL,conType,conRHS,conRange,TRUE);
	sciprint("Problem loaded into environment.\n");
	
	//code to give output
	cleanupBeforeExit();
	if(return0toScilab())
		return 1;
	
	return 0;
}

//basic problem loader, expects normal matrix. Not suitable for large problems
int sci_sym_loadProblemBasic(char *fname){
	
	if(commonCodePart1())
		return 1;
		
	//get input 7: matrix of constraint equation coefficients
	sciErr = getVarAddressFromPosition(pvApiCtx, 7, &varAddress);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		cleanupBeforeExit();return 1;
	}
	if ( !isDoubleType(pvApiCtx,varAddress) ||  isVarComplex(pvApiCtx,varAddress) )
	{
		Scierror(999, "Wrong type for input argument #7: A matrix of doubles is expected.\n");
		cleanupBeforeExit();return 1;
	}
	sciErr = getMatrixOfDouble(pvApiCtx, varAddress, &inputMatrixRows, &inputMatrixCols, &conVals);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		cleanupBeforeExit();return 1;
	}
	if(inputMatrixRows!=numConstr || inputMatrixCols!=numVars)
	{
		Scierror(999, "Wrong type for input argument #7: Incorrectly sized matrix.\n");
		cleanupBeforeExit();return 1;
	}

	conMatrixColStart=new int[numVars+1]; //start of each column of constraint matrix, used internally
	conMatrixRowIndex=new int[numVars*numConstr]; //index of column elements in each column, used internally
	for(colIter=0;colIter<numVars;colIter++){
		conMatrixColStart[colIter]=colIter*numConstr;
		for(rowIter=0;rowIter<numConstr;rowIter++){
			conMatrixRowIndex[colIter*numConstr+rowIter]=rowIter;
		}
	}
	conMatrixColStart[numVars]=numVars*numConstr;
	
	if(commonCodePart2())
		return 1;

	return 0;
}

//advanced problem loader, expects sparse matrix. For use with larger problems (>10 vars)
int sci_sym_loadProblem(char *fname){
	int retVal,nonZeros,*itemsPerRow,*colIndex,matrixIter,newPos,*oldRowIndex,*colStartCopy;
	double *data;
	
	if(commonCodePart1())
		return 1;
		
	//get input 7: matrix of constraint equation coefficients
	sciErr = getVarAddressFromPosition(pvApiCtx, 7, &varAddress);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		cleanupBeforeExit();return 1;
	}
	if ( !isSparseType(pvApiCtx,varAddress) ||  isVarComplex(pvApiCtx,varAddress) )
	{
		Scierror(999, "Wrong type for input argument #7: A sparse matrix of doubles is expected.\n");
		cleanupBeforeExit();return 1;
	}
	sciErr = getSparseMatrix(pvApiCtx,varAddress,&inputMatrixRows,&inputMatrixCols,&nonZeros,&itemsPerRow,&colIndex,&data);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		cleanupBeforeExit();return 1;
	}
	if(inputMatrixRows!=numConstr || inputMatrixCols!=numVars)
	{
		Scierror(999, "Wrong type for input argument #7: Incorrectly sized matrix.\n");
		cleanupBeforeExit();return 1;
	}
	
	//convert SciLab format sparse matrix into the format required by Symphony
	conVals=new double[nonZeros]; //matrix contents
	conMatrixColStart=new int[numVars+1]; //where each column of the matrix starts
	conMatrixRowIndex=new int[nonZeros]; //row number of each element
	oldRowIndex=new int[nonZeros]; //row number in old matrix
	colStartCopy=new int[numVars+1]; //temporary copy of conMatrixColStart
	for(rowIter=matrixIter=0;rowIter<numConstr;rowIter++) //assign row number to each element in old matrix
		for(colIter=0;colIter<itemsPerRow[rowIter];colIter++,matrixIter++)
			oldRowIndex[matrixIter]=rowIter;
	for(colIter=0;colIter<=numVars;colIter++) //initialize to 0
		conMatrixColStart[colIter]=0;
	for(matrixIter=0;matrixIter<nonZeros;matrixIter++) //get number of elements in each column
		conMatrixColStart[colIndex[matrixIter]]++;
	for(colIter=1;colIter<=numVars;colIter++){ //perfrom cumulative addition to get final data about where each column starts
		conMatrixColStart[colIter]+=conMatrixColStart[colIter-1];
		colStartCopy[colIter]=conMatrixColStart[colIter];
	}
	colStartCopy[0]=0;
	for(matrixIter=0;matrixIter<nonZeros;matrixIter++) //move data from old matrix to new matrix
	{
		newPos=colStartCopy[colIndex[matrixIter]-1]++; //calculate its position in the new matrix
		conVals[newPos]=data[matrixIter]; //move the data
		conMatrixRowIndex[newPos]=oldRowIndex[matrixIter]; //assign it its row number
	}
	
	retVal=commonCodePart2();
	
	//cleanup some more allocd memory
	if(conVals) delete[] conVals;
	if(oldRowIndex) delete[] oldRowIndex;
	if(colStartCopy) delete[] colStartCopy;
	
	return retVal;
}

}

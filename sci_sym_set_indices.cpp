/*
 * Implementation Symphony Tool Box for Scilab
 * sci_sym_set_indices.cpp
 * contains functions for setting index variables as continuous and integer values
 * By Iswarya 
 */

#include <symphony.h>
extern sym_environment* global_sym_env;//defined in globals.cpp

extern "C" {
#include <api_scilab.h>
#include <Scierror.h>
#include <BOOL.h>
#include <localization.h>
#include <sciprint.h>

//This function is for setting a index variable to be continuous
int sci_sym_set_continuous(char *fname, unsigned long fname_len){
	
	// Error management variable
	SciErr sciErr;
	double status=0.0;//assume error status
	int *piAddressVarOne = NULL;//pointer used to access argument of the function
	int index;//to indicate the index of the variable to be set continuous
	int output=0;//out parameter for the load mps function
	double num;//to store the index value obtained as double from scilab
	CheckInputArgument(pvApiCtx, 1, 1);//Check we have exactly one argument as input or not
	CheckOutputArgument(pvApiCtx, 1, 1);//Check we have exactly one argument on output side or not

	//load address of 1st argument into piAddressVarOne
	sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressVarOne);

	//check whether there is an error or not.
	if (sciErr.iErr){
        printError(&sciErr, 0);
        return 0;
	}
		
	//read the index position in the 'value' variable
	int err1=getScalarDouble(pvApiCtx, piAddressVarOne, &num);
	
	//check for the integrity of integer value obtained
	if((double)(unsigned int)num!=(double)num)
		return 0;
	else
		index=(unsigned int)num;//if the value passed is an integer ,store it as an unsigned integer in 'index' variable 


	//ensure that environment is active
	if(global_sym_env==NULL){
		sciprint("Error: Symphony environment not initialized. Please run 'sym_open()' first.\n");
		}
	else {
		output=sym_set_continuous(global_sym_env,index);//setting the variable continuous
		if(output==FUNCTION_TERMINATED_ABNORMALLY)
		{
			status=0.0;//function did not invoke successfully
			sciprint("Function terminated abnormally,didnot execute");
		}
		else if(output==FUNCTION_TERMINATED_NORMALLY)
		{
			status=1.0;//no error in executing the function
			sciprint("Function executed successfully");
		}
		
		
		}
	
	int e=createScalarDouble(pvApiCtx,nbInputArgument(pvApiCtx)+1,status);
	if (e){
		AssignOutputVariable(pvApiCtx, 1) = 0;
		return 1;
		}

	AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
	ReturnArguments(pvApiCtx);

	return 0;
	}


//This function is for setting a index variable to be continuous
int sci_sym_set_integer(char *fname, unsigned long fname_len){
	
	// Error management variable
	SciErr sciErr;
	double status=0.0;//assume error status
	int *piAddressVarOne = NULL;//pointer used to access argument of the function
	int index;//to indicate the index of the variable to be set continuous
	int output=0;//out parameter for the load mps function
	double num;//to store the index value obtained as double from scilab
	CheckInputArgument(pvApiCtx, 1, 1);//Check we have exactly one argument as input or not
	CheckOutputArgument(pvApiCtx, 1, 1);//Check we have exactly one argument on output side or not

	//load address of 1st argument into piAddressVarOne
	sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressVarOne);

	//check whether there is an error or not.
	if (sciErr.iErr){
        printError(&sciErr, 0);
        return 0;
	}
		
	//read the index position in the 'value' variable
	int err1=getScalarDouble(pvApiCtx, piAddressVarOne, &num);
	
	//check for the integrity of integer value obtained
	if((double)(unsigned int)num!=(double)num)
		return 0;
	else
		index=(unsigned int)num;//if the value passed is an integer ,store it as an unsigned integer in 'index' variable 


	//ensure that environment is active
	if(global_sym_env==NULL){
		sciprint("Error: Symphony environment not initialized. Please run 'sym_open()' first.\n");
		}
	else {
		output=sym_set_integer(global_sym_env,index);//setting the variable integer
		if(output==FUNCTION_TERMINATED_ABNORMALLY)
		{
			status=0.0;//function did not invoke successfully
			sciprint("Function terminated abnormally,didnot execute");
		}
		else if(output==FUNCTION_TERMINATED_NORMALLY)
		{
			status=1.0;//no error in executing the function
			sciprint("Function executed successfully");
		}
		
		
		}
	
	int e=createScalarDouble(pvApiCtx,nbInputArgument(pvApiCtx)+1,status);
	if (e){
		AssignOutputVariable(pvApiCtx, 1) = 0;
		return 1;
		}

	AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
	ReturnArguments(pvApiCtx);

	return 0;
	}





}


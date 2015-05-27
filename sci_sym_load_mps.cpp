/*
 * Implementation Symphony Tool Box for Scilab
 * template.cpp
 * contains function for loading .mps file to symphony
 * By Iswarya
 * Last edit on 20-05-2015 by Iswarya 
 */

#include <symphony.h>
extern sym_environment* global_sym_env;//defined in globals.cpp

extern "C" {
#include <api_scilab.h>
#include <Scierror.h>
#include <BOOL.h>
#include <localization.h>
#include <sciprint.h>

//This function is for loading a mps file to symphony
int sci_sym_load_mps(char *fname, unsigned long fname_len){
	
	// Error management variable
	SciErr sciErr;
	double status=0.0;//assume error status
	int *piAddressVarOne = NULL;//pointer used to access argument of the function
	char file[100];//string to hold the name of .mps file
	char* ptr=file;//pointer to point to address of file name
	int output=0;//out parameter for the load mps function
	CheckInputArgument(pvApiCtx, 1, 1);//Check we have exactly one argument as input or not
	CheckOutputArgument(pvApiCtx, 1, 1);//Check we have exactly one argument on output side or not

	//load address of 1st argument into piAddressVarOne
	sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressVarOne);

	//check whether there is an error or not.
	if (sciErr.iErr){
        printError(&sciErr, 0);
        return 0;
	}
	
	
	//read the value in that pointer pointing to file name
	int err=getAllocatedSingleString(pvApiCtx, piAddressVarOne, &ptr);

	//ensure that environment is active
	if(global_sym_env==NULL){
		sciprint("Error: Symphony environment not initialized. Please run 'sym_open()' first.\n");
		}
	else {
		output=sym_read_mps(global_sym_env,ptr);//loading .mps file to symphony
		if(output==FUNCTION_TERMINATED_ABNORMALLY)
		{
			status=0.0;//function did not invoke successfully
			sciprint("Function terminated abnormally,didnot execute\n");
		}
		else if(output==FUNCTION_TERMINATED_NORMALLY)
		{
			status=1.0;//no error in executing the function
			sciprint("Function executed successfully\n");
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


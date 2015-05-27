/*
 * Symphony Toolbox
 * Check if Symphony environment is active
 * Made by Keyur Joshi
 * Last edit on 20-5-15
 */

#include "symphony.h"

extern sym_environment* global_sym_env; //defined in globals.cpp

extern "C" {
#include "api_scilab.h"
#include "Scierror.h"
#include "sciprint.h"
#include "BOOL.h"
#include <localization.h>

int sci_sym_isEnvActive(char *fname){
	
	//error management variable
	SciErr sciErr;
	int iRet;
	
	//data declarations
	double returnVal;
	
	//code to check arguments and get them
	CheckInputArgument(pvApiCtx,0,0) ;
	CheckOutputArgument(pvApiCtx,1,1) ;
	
	//code to process input
	if(global_sym_env==NULL){
		sciprint("Symphony environment is not initialized. Please run 'sym_open()' first.\n");
		returnVal=0.0;
	}else{
		sciprint("Symphony environment is active and ready for use.\n");
		returnVal=1.0;
	}
	
	//code to give output
	iRet = createScalarDouble(pvApiCtx, nbInputArgument(pvApiCtx)+1, returnVal);
    if(iRet)
    {
        /* If error, no return variable */
        AssignOutputVariable(pvApiCtx, 1) = 0;
		ReturnArguments(pvApiCtx);
        return 1;
    }
	AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx)+1;
	
	ReturnArguments(pvApiCtx);
	return 0;
}

}

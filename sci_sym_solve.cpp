/*
 * Implementation Symphony Tool Box for Scilab
 * Contains sym_solve function
 * Author : Sai Kiran
 */

#include <symphony.h>
#include <sci_iofunc.hpp>
extern sym_environment* global_sym_env;//defined in globals.cpp

extern "C" {
#include <api_scilab.h>
#include <Scierror.h>
#include <BOOL.h>
#include <localization.h>
#include <sciprint.h>

int process_ret_val(int);

int sci_sym_solve(char *fname, unsigned long fname_len){
	
	int status=0; // Assuming abnormal termination
  
	//check whether we have no input and one output argument or not
	CheckInputArgument(pvApiCtx, 0, 0) ;//no input argument
	CheckOutputArgument(pvApiCtx, 1, 1) ;//one output argument

	// Check environment
	if(global_sym_env==NULL)
		sciprint("Error: Symphony environment is not initialized.\n");
	else // There is an environment opened
		status=process_ret_val(sym_solve(global_sym_env));// Call function
	// Return result to scilab
	return returnDoubleToScilab(status);
	}
}

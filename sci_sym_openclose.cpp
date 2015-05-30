/*
 * Symphony Tool Box for Scilab
 * contains functions that opens and closes the symphony environment 
 * By Keyur Joshi, Iswarya
 */
#include <symphony.h>
extern sym_environment* global_sym_env;//defined in globals.cpp

extern "C" {
#include <api_scilab.h>
#include <Scierror.h>
#include <BOOL.h>
#include <localization.h>
#include <sciprint.h>

/* Function that initializes the symphony environment
 * Returns 1 on success , 0 on failure
*/
int sci_sym_open(char *fname, unsigned long fname_len){

	// Error management variable
	SciErr sciErr;
	double status=0;
	
	//check whether we have no input and one output argument or not
	CheckInputArgument(pvApiCtx, 0, 0) ;//no input argument
	CheckOutputArgument(pvApiCtx, 1, 1) ;//one output argument

	//check environment
	if(global_sym_env!=NULL){
		sciprint("Warning: Symphony environment is already initialized.\n");
	}else {
		global_sym_env = sym_open_environment();//open an environment
		if (!global_sym_env)
			sciprint("Error: Unable to create symphony environment.\n");
		else {
			status=1;
			sciprint("Symphony environment is created successfully. Please run 'sym_close()' to close.\n");
			}
		}

	/*write satus of function (success-1 or failure-0) as output argument to scilab*/
	int err=createScalarDouble(pvApiCtx,nbInputArgument(pvApiCtx)+1,status);//copy status to scilab
	if (err){//error while writing status
		AssignOutputVariable(pvApiCtx, 1) = 0;
		return 1;
		}
	//assign status position to output argument
	AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
	ReturnArguments(pvApiCtx);
	return 0;
	}

/*Function that closes symphony environment
 * Returns 1 on success , 0 on failure
*/
int sci_sym_close(char *fname, unsigned long fname_len){
	
	// Error management variable
	SciErr sciErr;
	double status=0;
	int output;//output parameter for closing the environment
    

  	//check whether we have no input and one output argument or not
	CheckInputArgument(pvApiCtx, 0, 0) ;//no input argument
	CheckOutputArgument(pvApiCtx, 1, 1) ;//one output argument

	if (global_sym_env==NULL){//check for environment
		sciprint("Error: symphony environment is not initialized.\n");
	}else {
		output=sym_close_environment(global_sym_env);//close environment
		if(output==ERROR__USER){	
			status=0;//User error detected in user_free_master() function or when function invoked unsuccessfully
			sciprint("Error in user_free_master()");
			}
		else if(output==FUNCTION_TERMINATED_ABNORMALLY){
			status=0;//function invoked unsuccessfully
			sciprint("Symphony environment could not be closed.\n");
			}
		else if(output==FUNCTION_TERMINATED_NORMALLY){			
			status=1;//function invoked successfully and no error
			global_sym_env=NULL;//important to set to NULL, so that other functions can detect that environment is not open.
			sciprint("Symphony environement closed successfully. Please run 'sym_open()' to restart.\n\n");
			}
		
		}

	/*write satus of function (success-1 or failure-0) as output argument to scilab
	*/
	int err=createScalarDouble(pvApiCtx,nbInputArgument(pvApiCtx)+1,status);//copy status to scilab
	if (err){//error while writing status
		AssignOutputVariable(pvApiCtx, 1) = 0;
		return 1;
		}
	//assign status position to output argument
	AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
	ReturnArguments(pvApiCtx);//return arguments to scilab
	return 0;
	}
}

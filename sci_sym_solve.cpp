/*
 * Implementation Symphony Tool Box for Scilab
 * solver_status_query_functions.cpp
 * contains Solve Function
 * 20-05-2015 (sai kiran)
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

extern double process_ret_val(int);

int sci_sym_solve(char *fname, unsigned long fname_len){
	// Error management variable
	SciErr sciErr;
	double status=0.0;//assuming there is an error
  
	//check whether we have no input and one output argument or not
	CheckInputArgument(pvApiCtx, 0, 0) ;//no input argument
	CheckOutputArgument(pvApiCtx, 1, 1) ;//one output argument

	//check environment
	if(global_sym_env==NULL)
		sciprint("Error: Symphony environment is not initialized.\n");
	else {//there is an environment opened
		int ret_val=sym_solve(global_sym_env);//call the symphony function
		status=process_ret_val(ret_val);
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
	ReturnArguments(pvApiCtx);
	return 0;
	}
}

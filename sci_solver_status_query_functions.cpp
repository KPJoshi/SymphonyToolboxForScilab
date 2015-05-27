/*
 * Implementation Symphony Tool Box for Scilab
 * solver_status_query_functions.cpp
 * contains Solver Status Query Functions (7 functions)
 * Author: sai kiran
 */

#include <symphony.h>
extern sym_environment* global_sym_env;//defined in globals.cpp

extern "C" {
#include <api_scilab.h>
#include <Scierror.h>
#include <BOOL.h>
#include <localization.h>
#include <sciprint.h>

extern double process_ret_val(int);
/* Function that initializes the symphony environment
 * Returns 1 on success , 0 on failure
*/

int sci_sym_get_status(char *fname, unsigned long fname_len){
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
		int ret_val=sym_get_status(global_sym_env);//call the symphony function
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

int sci_sym_is_proven_optimal(char *fname, unsigned long fname_len){
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
		int ret_val=sym_is_proven_optimal(global_sym_env);//call the symphony function
		switch(ret_val){
			case TRUE:
				sciprint("\nThe problem was solved to optimality.\n");
				status=1.0;
				break;
			case FALSE:
				sciprint("\nThe problem was not solved to optimality.\n");
				status=1.0;
				break;
			default:
				sciprint("Error: Undefined return value.\n");
				break;			
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
	ReturnArguments(pvApiCtx);
	return 0;
	}

int sci_sym_is_proven_primal_infeasible(char *fname, unsigned long fname_len){
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
		int ret_val=sym_is_proven_primal_infeasible(global_sym_env);//call the symphony function
		switch(ret_val){
			case TRUE:
				sciprint("\nThe problem was proven to be infeasible.\n");
				status=1.0;
				break;
			case FALSE:
				sciprint("\nThe problem was not proven to be infeasible.\n");
				status=1.0;
				break;
			default:
				sciprint("Error: Undefined return value.\n");
				break;			
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
	ReturnArguments(pvApiCtx);
	return 0;
	}

int sci_sym_is_abandoned(char *fname, unsigned long fname_len){
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
		int ret_val=sym_is_abandoned(global_sym_env);//call the symphony function
		switch(ret_val){
			case TRUE:
				sciprint("\nThe problem was abandoned.\n");
				status=1.0;
				break;
			case FALSE:
				sciprint("\nThe problem was not abandoned.\n");
				status=1.0;
				break;
			default:
				sciprint("Error: Undefined return value.\n");
				break;
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
	ReturnArguments(pvApiCtx);
	return 0;
	}

int sci_sym_is_iteration_limit_reached(char *fname, unsigned long fname_len){
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
		int ret_val=sym_is_iteration_limit_reached(global_sym_env);//call the symphony function
		switch(ret_val){
			case TRUE:
				sciprint("\nThe iteration limit is reached.\n");
				status=1.0;
				break;
			case FALSE:
				sciprint("\nThe iteration limit is not reached.\n");
				status=1.0;
				break;
			default:
				sciprint("Error: Undefined return value.\n");
				break;
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
	ReturnArguments(pvApiCtx);
	return 0;
	}

int sci_sym_is_time_limit_reached(char *fname, unsigned long fname_len){
	double status=0.0;//assuming there is an error
  
	//check whether we have no input and one output argument or not
	CheckInputArgument(pvApiCtx, 0, 0) ;//no input argument
	CheckOutputArgument(pvApiCtx, 1, 1) ;//one output argument

	//check environment
	if(global_sym_env==NULL)
		sciprint("Error: Symphony environment is not initialized.\n");
	else {//there is an environment opened
		int ret_val=sym_is_time_limit_reached(global_sym_env);//call the symphony function
		switch(ret_val){
			case TRUE:
				sciprint("\nTime limit was reached.\n");
				status=1.0;
				break;
			case FALSE:
				sciprint("\nTime limit was not reached.\n");
				status=1.0;
				break;
			default:
				sciprint("Error: Undefined return value.\n");
				break;
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
	ReturnArguments(pvApiCtx);
	return 0;
	}

int sci_sym_is_target_gap_achieved(char *fname, unsigned long fname_len){
	double status=0.0;//assuming there is an error
  
	//check whether we have no input and one output argument or not
	CheckInputArgument(pvApiCtx, 0, 0) ;//no input argument
	CheckOutputArgument(pvApiCtx, 1, 1) ;//one output argument

	//check environment
	if(global_sym_env==NULL)
		sciprint("Error: Symphony environment is not initialized.\n");
	else {//there is an environment opened
		int ret_val=sym_is_target_gap_achieved(global_sym_env);//call the symphony function
		switch(ret_val){
			case TRUE:
				sciprint("\nTarget gap was reached.\n");
				status=1.0;
				break;
			case FALSE:
				sciprint("\nTarget gap was not reached.\n");
				status=1.0;
				break;
			default:
				sciprint("Error: Undefined return value.\n");
				break;
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
	ReturnArguments(pvApiCtx);
	return 0;
	}
}


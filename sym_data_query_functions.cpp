/*
 * Implementation Symphony Tool Box for Scilab
 * sym_data_query_functions.cpp
 * contains Data Query Functions
 * Author: Sai Kiran
 */

#include <symphony.h>
extern sym_environment* global_sym_env;//defined in globals.cpp
//extern MIPdesc * problem_desc;

extern "C" {
#include <api_scilab.h>
#include <Scierror.h>
#include <BOOL.h>
#include <localization.h>
#include <sciprint.h>
#include <string.h> //included to compare function names (for only this file)

extern double process_ret_val(int);
/* Function that initializes the symphony environment
 * Returns 1 on success , 0 on failure
*/

//this function takes a function pointer(sym_get_num_cols or sym_get_num_ros or sym_get_num_elements)
int get_num(int (*fun)(sym_environment*,int*)){
	int num=0;
	int ret_val=fun(global_sym_env,&num);//call the function
	if (ret_val == FUNCTION_TERMINATED_NORMALLY){
		sciprint("\nFunction invoked successfully.\n");
		return num;
	}
	sciprint("\nFunction invoked unsuccessfully.\n");
	return 0;
}

//Generelized function for sym_getNumCols, sym_getNumRows,sym_get_NumElements
int sci_sym_get_num(char *fname, unsigned long fname_len){
	// Error management variable
	SciErr sciErr;
	double status=0.0;//assuming there is an error
	int num=0;//no. of columns or rows will be stored here...
  
	//check whether we have no input and one output argument or not
	CheckInputArgument(pvApiCtx, 0, 0) ;//no input argument
	CheckOutputArgument(pvApiCtx, 1, 1) ;//one output argument
	
	int (*fun)(sym_environment*,int*) = NULL;
	if (!(strcmp(fname,"sym_getNumCols")))
		fun=sym_get_num_cols;
	else if (!(strcmp(fname,"sym_getNumRows")))//sym_getNumRows
		fun=sym_get_num_rows;
	
	else //sym_getNumElements
		fun=sym_get_num_elements;
	//check environment
	if(global_sym_env==NULL)
		sciprint("Error: Symphony environment is not initialized.\n");
	else //there is an environment opened
		num=get_num(fun);//we will get number of columns
	
	int err=createScalarDouble(pvApiCtx,nbInputArgument(pvApiCtx)+1,num);//copy status to scilab
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

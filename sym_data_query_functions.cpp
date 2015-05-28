/*
 * Implementation Symphony Tool Box for Scilab
 * sym_data_query_functions.cpp
 * contains Data Query Functions
 * Author: Sai Kiran
 */

#include <symphony.h>
extern sym_environment* global_sym_env;//defined in globals.cpp

extern "C" {
#include <api_scilab.h>
#include <Scierror.h>
#include <BOOL.h>
#include <localization.h>
#include <sciprint.h>

#include <string.h>

/* This function takes a function pointer as argument that can be
 * sym_get_num_cols or
 * sym_get_num_ros or
 * sym_get_num_elements
 * and return the result of the function
*/
static int get_num_int(int (*fun)(sym_environment*,int*)){
	int num=0;
	int ret_val=fun(global_sym_env,&num);//call the function
	if (ret_val == FUNCTION_TERMINATED_NORMALLY){
		sciprint("\nFunction invoked successfully.\n");
		return num;
		}
	sciprint("\nFunction invoked unsuccessfully.\n");
	return 0;
	}

/* This function takes a function pointer and pointer to array of doubles as arguments
 * The functions are
 *  sym_get_col_lower
 *  sym_get_col_upper
 *  sym_get_rhs
 *  sym_get_row_range
 *  sym_get_row_lower
 *  sym_get_row_upper
 * and write the ouput of the function to pointer to array of double values.
*/
static int get_arr_dbl( int (*fun)(sym_environment* ,double* ),double* arr){
	int ret_val = fun(global_sym_env,arr);
	if (ret_val == FUNCTION_TERMINATED_NORMALLY) return 1;
	return 0;	
	}

/*
 * Generelized function for sym_getNumCols,
 * sym_getNumRows,sym_get_NumElements
*/
int sci_sym_get_num_int(char *fname, unsigned long fname_len){

	int result=0;/* Result of the callar */
  
	//check whether we have no input and one output argument or not
	CheckInputArgument(pvApiCtx, 0, 0) ; //no input argument
	CheckOutputArgument(pvApiCtx, 1, 1) ; //one output argument

	/* Array of possible callers of this function */
	char* arr_caller[]={"sym_getNumRows","sym_getNumCols","sym_getNumElements"};

	/* Array of functions to be called */
	int (*fun[])(sym_environment*,int*)= { sym_get_num_rows,
											sym_get_num_cols,
											sym_get_num_elements
											};
	
	if(global_sym_env==NULL) //There is no environment opened.
		sciprint("Error: Symphony environment is not initialized.\n");
	else {
		//There is an environment opened
		int iter=0,length=sizeof(arr_caller)/sizeof(char*),found_at= -1;
		for (;iter < length ;++iter){
			if (!strcmp(fname,arr_caller[iter]))
				found_at=iter;
			}
		if (found_at != -1)
			result=get_num_int(fun[found_at]);
		else //very rare case
			sciprint("\nError in function mapping in scilab script\n");
		}
	
	//Copy the result to scilab. Location is position next to input arguments.
	int err=createScalarDouble(pvApiCtx,nbInputArgument(pvApiCtx)+1,result);
	if (err){//error while writing result to scilab
		AssignOutputVariable(pvApiCtx, 1) = 0;
		return 1;
		}

	//assign result position to output argument
	AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
	ReturnArguments(pvApiCtx);
	return 0;
	}

/* This is generelized function for 
 * sym_getColLower,sym_getColUpper,sym_getRhs,sym_getRowRange,sym_getRowLower
 * and sym_getRowUpper.
 * (Functions taking symphony env and pointer to array of doubles as arguments)
*/
int sci_sym_get_dbl_arr(char *fname, unsigned long fname_len){

	int result_len=0;/* Length of the output double array */
	double *result=NULL;/* Pointer to output double array */
  
	//check whether we have no input and one output argument or not
	CheckInputArgument(pvApiCtx, 0, 0) ; //no input argument
	CheckOutputArgument(pvApiCtx, 1, 1) ; //one output argument
	
	/* Array of possible callers of this function */
	char* arr_caller[]={"sym_getColLower","sym_getColUpper",
						"sym_getRhs","sym_getRowRange",
						"sym_getRowLower","sym_getRowUpper"};

	/* Array of functions to be called */
	int (*fun[])(sym_environment*,double*)= {sym_get_col_lower,sym_get_col_upper,
											 sym_get_rhs,sym_get_row_range,
											 sym_get_row_lower,sym_get_row_upper};
	
	/* Array of functions the above functions depend on */
	int (*fun_depends[])(sym_environment*,int*) = {sym_get_num_cols,sym_get_num_cols,
													sym_get_num_rows,sym_get_num_rows,
													sym_get_num_rows,sym_get_num_rows};

	
	if(global_sym_env==NULL) //There is no environment opened.
		sciprint("Error: Symphony environment is not initialized.\n");
	else {
		//There is an environment opened
		int iter=0,length=sizeof(arr_caller)/sizeof(char*),found_at= -1;
		for (;iter < length ;++iter){
			if (!strcmp(fname,arr_caller[iter]))
				found_at=iter;
			}
		if (found_at != -1){
			result_len=get_num_int(fun_depends[found_at]);
		//	sciprint("\nLength is %d\n",result_len);
			result=(double*)malloc( sizeof(double) * result_len );
			if (result_len && get_arr_dbl(fun[found_at],result));
			if ( (!result_len) ) sciprint("\n No problem found. \n");
			}
		else //very rare case
			sciprint("\nError in function mapping in scilab script\n");
		}

	//Copy the result to scilab. Location is position next to input arguments.
	SciErr err=createMatrixOfDouble(pvApiCtx,nbInputArgument(pvApiCtx)+1,1,result_len,result);
	free(result); //Free the allocated space
	result=NULL; //Set to NULL
	if (err.iErr){ //Process error
        printError(&err, 0);
        return 0;
    	}

	//assign result position to output argument
	AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
	ReturnArguments(pvApiCtx);
	return 0;
	}

}

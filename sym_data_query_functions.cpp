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

void show_termination_status(int status) {
	if (status == FUNCTION_TERMINATED_NORMALLY)
		sciprint("\nFunction invoked successfully.\n");
	else
		sciprint("\nFunction invoked unsuccessfully.\n");	
	}

/* This function takes a function pointer as argument that can be
 * sym_get_num_cols or
 * sym_get_num_ros or
 * sym_get_num_elements
 * and return the result of the function
*/
static int get_num_int(int (*fun)(sym_environment*,int*) , int* result){
	return fun(global_sym_env,result);//call the function
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
	return fun(global_sym_env,arr);
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
		if (found_at != -1) {
			int ret_val=get_num_int(fun[found_at],&result);
			show_termination_status(ret_val);
			if (ret_val == FUNCTION_TERMINATED_ABNORMALLY)
				result=0;
			}
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
			int status1=get_num_int(fun_depends[found_at],&result_len);
			if ( status1 == FUNCTION_TERMINATED_NORMALLY && result_len ) {
				result=(double*)malloc( sizeof(double) * result_len );
				int ret_val=get_arr_dbl(fun[found_at],result);
				show_termination_status(ret_val);
				if (ret_val == FUNCTION_TERMINATED_ABNORMALLY)
					result_len=0;
				}
			else
				sciprint("\n No problem found. \n");
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

int sci_sym_get_matrix(char *fname, unsigned long fname_len){
	int num_ele=0;// No.of non-zero elements of the matrix
	int *matbeg=NULL;// Starting indices of each column 
	int *matind=NULL;// Row indices corresponding to each entry of matval
	double *matval=NULL;// Non-zero elements of matrix
	
	//check whether we have no input and one output argument or not
	CheckInputArgument(pvApiCtx, 0, 0) ; //no input argument
	CheckOutputArgument(pvApiCtx, 1, 1) ; //one output argument

	if(global_sym_env==NULL) //There is no environment opened.
		sciprint("Error: Symphony environment is not initialized.\n");
	else {
		int status1=get_num_int(sym_get_num_elements,&num_ele);
		sciprint("\n num_ele : %d \n",num_ele);
		int cols=0;
		int status2=get_num_int(sym_get_num_cols,&cols);
		int status3=FUNCTION_TERMINATED_ABNORMALLY;
		if (status1 == status2 && status1 == FUNCTION_TERMINATED_NORMALLY){
			int arr_col_index[cols+1];
			int arr_row_index[num_ele];
			double mat[num_ele];
			matbeg=arr_col_index;
			matind=arr_row_index;
			matval=mat;
			status3=sym_get_matrix(global_sym_env,&num_ele,matbeg,matind,matval);
			if (status1 == status3)
				show_termination_status(FUNCTION_TERMINATED_NORMALLY);
			else {
				show_termination_status(FUNCTION_TERMINATED_ABNORMALLY);
				sciprint("\n No problem found. \n");			
				//set to null
				}				
			}
		else {
			sciprint("\n else 2\n");
			show_termination_status(FUNCTION_TERMINATED_ABNORMALLY);
			//set to null
			}
			
		}
	
	//Copy the result to scilab. Location is position next to input arguments.
	int err=createScalarDouble(pvApiCtx,nbInputArgument(pvApiCtx)+1,0.0);
	if (err){//error while writing result to scilab
		AssignOutputVariable(pvApiCtx, 1) = 0;
		return 1;
		}

	//assign result position to output argument
	AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
	ReturnArguments(pvApiCtx);
	return 0;
	}
}

/*
 * Implementation Symphony Tool Box for Scilab
 * set_sym_remove.cpp
 * contains function for removing columns and rows
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
//function to remove specified columns
int sci_sym_delete_cols(char *fname, unsigned long fname_len){
	
	// Error management variable
	SciErr sciErr1,sciErr2;
	double status=0.0;//assume error status
	double num;//variable to store the number of columns to be deleted obtained from user in scilab
	int count=0;//iterator variable
	int num_cols;//stores the number of columns in the loaded problem
	int iType= 0;//stores the datatype of matrix 
	int rows=0,columns=0;//integer variables to denote the number of rows and columns in the array denoting the column numbers to be deleted
	unsigned int *value=NULL;//pointer to integer array allocated dynamically having the indices to be deleted
	double *array_ptr=NULL;//double array pointer to the array denoting the column numbers to be deleted
	int *piAddressVarOne = NULL,*piAddressVarTwo = NULL;//pointer used to access first and second arguments of the function
	int output=0;//output parameter for the symphony sym_delete_cols function
	CheckInputArgument(pvApiCtx, 2, 2);//Check we have exactly one argument as input or not
	CheckOutputArgument(pvApiCtx, 1, 1);//Check we have exactly one argument on output side or not

	//load address of 1st argument into piAddressVarOne
	sciErr1 = getVarAddressFromPosition(pvApiCtx, 1, &piAddressVarOne);
	//load address of 2nd argument into piAddressVarTwo
	sciErr2=getVarAddressFromPosition(pvApiCtx,2,&piAddressVarTwo);

	//Getting the first argument as a double value and storing in num
	int err1=getScalarDouble(pvApiCtx, piAddressVarOne, &num);
	//check whether there is an error or not.
	if (sciErr1.iErr){
        printError(&sciErr1, 0);
        return 0;
	}
	if (sciErr2.iErr){
        printError(&sciErr2, 0);
        return 0;
	}

	//check if it is double type
	sciErr2 = getVarType(pvApiCtx, piAddressVarTwo, &iType);
	if(sciErr2.iErr || iType != sci_matrix)
	{
		printError(&sciErr2, 0);
		return 0;
	}

		
	//getting the second argument as a double array
	sciErr2=getMatrixOfDouble(pvApiCtx,piAddressVarTwo,&rows,&columns,&array_ptr);
	if (sciErr2.iErr){
        printError(&sciErr2, 0);
        return 0;
	}

	//dynamically allocate the integer array 
	value=(unsigned int *)malloc(sizeof(unsigned int)*columns);
	//store double values in the integer array by typecasting
	while(count<columns)
	{
		value[count]=(unsigned int)array_ptr[count];
		count++;
	}	
	sciprint("\n");

	//ensure that environment is active

	if(global_sym_env==NULL){
		sciprint("Error: Symphony environment not initialized. Please run 'sym_open()' first.\n");
		}
	else {
		output=sym_get_num_cols(global_sym_env,&num_cols);//function to find the number of columns in the loaded problem
		if(output==FUNCTION_TERMINATED_ABNORMALLY)
		{
			Scierror(999, "An error occured. Has a problem been loaded?\n");
			return 0;
		}
		//only when the number of columns to be deleted is lesser than the actual number of columns ,execution is proceeded with
		if(columns<=num_cols){
		output=sym_delete_cols(global_sym_env,(unsigned int)num,value);//symphony function to delete the columns specified
		if(output==FUNCTION_TERMINATED_NORMALLY)
		{
			sciprint("Execution is successfull\n");
			status=1.0;
		}
		else if(output==FUNCTION_TERMINATED_ABNORMALLY)
		{
			Scierror(999,"Problem occured while deleting the columns,Are the column numbers correct?\n");
			sciprint("Function terminated abnormally\n");
			status=0.0;
		}
	}
		else{
			sciprint("These many number of variables dont exist in the problem\n");
			status=0.0;
		}
				
	}
	
	int e=createScalarDouble(pvApiCtx,nbInputArgument(pvApiCtx)+1,status);
	if (e){
		AssignOutputVariable(pvApiCtx, 1) = 0;
		return 1;
		}

	AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
	ReturnArguments(pvApiCtx);
	free(value);//freeing the memory of the allocated pointer
	return 0;
	}


//function to remove specified rows
int sci_sym_delete_rows(char *fname, unsigned long fname_len){
	
	// Error management variable
	SciErr sciErr1,sciErr2;
	double status=0.0;//assume error status
	double num;//variable to store the number of rows to be deleted obtained from user in scilab
	int count=0;//iterator variable
	int num_rows;//stores the number of columns in the loaded problem
	int iType= 0;//stores the datatype of matrix 
	int rows=0,columns=0;//integer variables to denote the number of rows and columns in the array denoting the row numbers to be deleted
	unsigned int *value=NULL;//pointer to integer array allocated dynamically having the indices to be deleted
	double *array_ptr=NULL;//double array pointer to the array denoting the rows numbers to be deleted
	int *piAddressVarOne = NULL,*piAddressVarTwo = NULL;//pointer used to access first and second arguments of the function
	int output=0;//output parameter for the symphony sym_delete_rows function
	CheckInputArgument(pvApiCtx, 2, 2);//Check we have exactly one argument as input or not
	CheckOutputArgument(pvApiCtx, 1, 1);//Check we have exactly one argument on output side or not

	//load address of 1st argument into piAddressVarOne
	sciErr1 = getVarAddressFromPosition(pvApiCtx, 1, &piAddressVarOne);
	//load address of 2nd argument into piAddressVarTwo
	sciErr2=getVarAddressFromPosition(pvApiCtx,2,&piAddressVarTwo);

	//Getting the first argument as a double value and storing in num
	int err1=getScalarDouble(pvApiCtx, piAddressVarOne, &num);
	//check whether there is an error or not.
	if (sciErr1.iErr){
        printError(&sciErr1, 0);
        return 0;
	}
	if (sciErr2.iErr){
        printError(&sciErr2, 0);
        return 0;
	}

	//check if it is double type
	sciErr2 = getVarType(pvApiCtx, piAddressVarTwo, &iType);
	if(sciErr2.iErr || iType != sci_matrix)
	{
		printError(&sciErr2, 0);
		return 0;
	}

		
	//getting the second argument as a double array
	sciErr2=getMatrixOfDouble(pvApiCtx,piAddressVarTwo,&rows,&columns,&array_ptr);
	if (sciErr2.iErr){
        printError(&sciErr2, 0);
        return 0;
	}

	//dynamically allocate the integer array 
	value=(unsigned int *)malloc(sizeof(unsigned int)*columns);
	//store double values in the integer array by typecasting
	while(count<columns)
	{
		value[count]=(unsigned int)array_ptr[count];
		count++;
	}	
	sciprint("\n");

	//ensure that environment is active

	if(global_sym_env==NULL){
		sciprint("Error: Symphony environment not initialized. Please run 'sym_open()' first.\n");
		}
	else {
		output=sym_get_num_rows(global_sym_env,&num_rows);//function to find the number of rows in the loaded problem
		if(output==FUNCTION_TERMINATED_ABNORMALLY)
		{
			Scierror(999, "An error occured. Has a problem been loaded?\n");
			return 0;
		}
		//only when the number of rows to be deleted is lesser than the actual number of rows ,execution is proceeded with
		if(columns<=num_rows){
		output=sym_delete_rows(global_sym_env,(unsigned int)num,value);//symphony function to delete the rows specified
		if(output==FUNCTION_TERMINATED_NORMALLY)
		{
			sciprint("Execution is successfull\n");
			status=1.0;
		}
		else if(output==FUNCTION_TERMINATED_ABNORMALLY)
		{
			Scierror(999,"Problem occured while deleting the columns,Are the column numbers correct?\n");
			sciprint("Function terminated abnormally\n");
			status=0.0;
		}
	}
		else{
			sciprint("These many number of constraints dont exist in the problem\n");
			status=0.0;
		}
				
	}
	
	int e=createScalarDouble(pvApiCtx,nbInputArgument(pvApiCtx)+1,status);
	if (e){
		AssignOutputVariable(pvApiCtx, 1) = 0;
		return 1;
		}

	AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
	ReturnArguments(pvApiCtx);
	free(value);//freeing the memory of the allocated pointer
	return 0;
	}





}

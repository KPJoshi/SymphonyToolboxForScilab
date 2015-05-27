/*
 * Implementation Symphony Tool Box for Scilab
 * globals.cpp
 * contains definitions of global variables and functions
 * By Keyur Joshi and Sai Kiran
 * Last edit on 21-05-2015 by Sai Kiran
 */
#include <symphony.h>
#include <sciprint.h>

sym_environment *global_sym_env=0;

extern "C"{
double process_ret_val(int ret_val){
	double status=0.0;
	switch(ret_val){
		case ERROR__USER:
			sciprint("\nError. User error detected in one of"
			"sci_user_send_lp_data(),"
			"sci_user_send_cg_data(),"
			"user_send_cp_data(),"
			"user_receive_feasible_solution(),"
			"user_display_solution(),"
			"user_process_own_messages() functions.\n");
			break;
		case TM_OPTIMAL_SOLUTION_FOUND:
			sciprint("\nTree Manager (TM) found the optimal solution and stopped.\n");
			status=1.0;
			break;
		case TM_TIME_LIMIT_EXCEEDED:
			sciprint("\nTM stopped after reaching the predefined time limit.\n");
			status=1.0;
			break;
		case TM_NODE_LIMIT_EXCEEDED:
			sciprint("\nTM stopped after reaching the predefined node limit.\n");
			status=1.0;
			break;
		case TM_TARGET_GAP_ACHIEVED:
			sciprint("\nTM stopped after achieving the predefined target gap.\n");
			status=1.0;				
			break;
		case TM_FOUND_FIRST_FEASIBLE:
			sciprint("\nTM stopped after finding the first feasible solution.\n");
			status=1.0;				
			break;
		case TM_ERROR__NO_BRANCHING_CANDIDATE:
			sciprint("\nError. TM stopped. User didn’t select branching candidate in user select candidates() callback\n");
			break;
		case TM_ERROR__ILLEGAL_RETURN_CODE:
			sciprint("\nError. TM stopped after getting an invalid return code.\n");
			break;
		case TM_ERROR__NUMERICAL_INSTABILITY:
			sciprint("\nError. TM stopped due to some numerical difficul-ties.\n");
			break;
		case TM_ERROR__COMM_ERROR:
			sciprint("\nError. TM stopped due to communication error.\n");
			break;
		case TM_ERROR__USER:
			sciprint("\nError. TM stopped. User error detected in one of user callbacks called during TM processes.\n");
		default:
			sciprint("\nError. Undefined return value .\n");
			break;
		}
	return status;
	}
}

/*
 * Implementation Symphony Tool Box for Scilab
 * globals.cpp
 * contains definitions of global variables and functions
 * By Keyur Joshi and Sai Kiran
 */
#include <symphony.h>
#include <sciprint.h>

sym_environment *global_sym_env=0;

extern "C"{
int process_ret_val(int ret_val){
	int status=0;
	sciprint("\n");
	switch(ret_val){
		case TM_NO_PROBLEM:
			sciprint("TM_NO_PROBLEM");
			break;
		case TM_NO_SOLUTION:
			sciprint("TM_NO_SOLUTION");
			break;
		case TM_FINISHED:
			sciprint("TM_FINISHED");
			break;
		case TM_UNFINISHED:
			sciprint("TM_UNFINISHED");
			break;
		case TM_FEASIBLE_SOLUTION_FOUND:
			sciprint("TM_FEASIBLE_SOLUTION_FOUND");
			break;
		case TM_SIGNAL_CAUGHT:
			sciprint("TM_SIGNAL_CAUGHT");
			break;
		case TM_UNBOUNDED:
			sciprint("TM_UNBOUNDED");
			break;
		case PREP_OPTIMAL_SOLUTION_FOUND:
			sciprint("PREP_OPTIMAL_SOLUTION_FOUND");
			break;
		case PREP_NO_SOLUTION:
			sciprint("PREP_NO_SOLUTION");
			break;
		case PREP_ERROR:
			sciprint("PREP_ERROR");
			status=1;
			break;
		case ERROR__USER:
			sciprint("Error. User error detected in one of"
			"sci_user_send_lp_data(),"
			"sci_user_send_cg_data(),"
			"user_send_cp_data(),"
			"user_receive_feasible_solution(),"
			"user_display_solution(),"
			"user_process_own_messages() functions.");
			status=1;
			break;
		case TM_OPTIMAL_SOLUTION_FOUND:
			sciprint("Tree Manager (TM) found the optimal solution and stopped.");
			status=0;
			break;
		case TM_TIME_LIMIT_EXCEEDED:
			sciprint("TM stopped after reaching the predefined time limit.");
			status=0;
			break;
		case TM_NODE_LIMIT_EXCEEDED:
			sciprint("TM stopped after reaching the predefined node limit.");
			break;
		case TM_TARGET_GAP_ACHIEVED:
			sciprint("TM stopped after achieving the predefined target gap.");
			break;
		case TM_FOUND_FIRST_FEASIBLE:
			sciprint("TM stopped after finding the first feasible solution.");
			break;
		case TM_ERROR__NO_BRANCHING_CANDIDATE:
			sciprint("Error. TM stopped. User didn’t select branching candidate in user select candidates() callback");
			status=1;			
			break;
		case TM_ERROR__ILLEGAL_RETURN_CODE:
			sciprint("Error. TM stopped after getting an invalid return code.");
			status=1;			
			break;
		case TM_ERROR__NUMERICAL_INSTABILITY:
			sciprint("Error. TM stopped due to some numerical difficulties.");
			status=1;			
			break;
		case TM_ERROR__COMM_ERROR:
			sciprint("Error. TM stopped due to communication error.");
			status=1;			
			break;
		case TM_ERROR__USER:
			sciprint("Error. TM stopped. User error detected in one of user callbacks called during TM processes.");
		default:
			sciprint("Error. Undefined return value .");
			status=1;			
			break;
		}
	sciprint("\n");
	return status;
	}
}

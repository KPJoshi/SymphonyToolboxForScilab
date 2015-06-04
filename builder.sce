mode(-1)
lines(0)

//Symphony toolbox builder
//By Keyur Joshi, Sai Kiran and Iswarya

WITHOUT_AUTO_PUTLHSVAR = %t;

tbx_build_gateway("symphonytools", ..
	[
		"sym_open","sci_sym_open";
		"sym_close","sci_sym_close";
		"sym_loadProblemBasic","sci_sym_loadProblemBasic";
		"sym_loadProblem","sci_sym_loadProblem";
		"sym_isEnvActive","sci_sym_isEnvActive";
		"sym_loadMPS","sci_sym_load_mps";
		"sym_getStatus","sci_sym_get_status";
		"sym_solve","sci_sym_solve";
		"sym_isOptimal","sci_sym_get_solver_status";
		"sym_isInfeasible","sci_sym_get_solver_status";
		"sym_isAbandoned","sci_sym_get_solver_status";
		"sym_isIterLimitReached","sci_sym_get_solver_status";
		"sym_isTimeLimitReached","sci_sym_get_solver_status";
		"sym_isTargetGapAchieved","sci_sym_get_solver_status";
		"sym_isContinuous","sci_sym_isContinuous";
		"sym_isBinary","sci_sym_isBinary";
		"sym_isInteger","sci_sym_isInteger";
		"sym_getInfinity","sci_sym_getInfinity";
		"sym_getVarSoln","sci_sym_getVarSoln";
		"sym_getObjVal","sci_sym_getObjVal";
		"sym_getNumConstr","sci_sym_get_num_int";
		"sym_getNumVar","sci_sym_get_num_int";
		"sym_getNumElements","sci_sym_get_num_int";
		"sym_getVarLower","sci_sym_get_dbl_arr";
		"sym_getVarUpper","sci_sym_get_dbl_arr";
		"sym_getRhs","sci_sym_get_dbl_arr";
		"sym_getConstrRange","sci_sym_get_dbl_arr";
		"sym_getConstrLower","sci_sym_get_dbl_arr";
		"sym_getConstrUpper","sci_sym_get_dbl_arr";
		"sym_getObjCoeff","sci_sym_get_dbl_arr";
		"sym_set_defaults","sci_sym_set_defaults";
		"sym_set_int_param","sci_sym_set_int_param";
		"sym_get_int_param","sci_sym_get_int_param";
		"sym_set_dbl_param","sci_sym_set_dbl_param";
		"sym_get_dbl_param","sci_sym_get_dbl_param";
		"sym_set_str_param","sci_sym_set_str_param";
		"sym_get_str_param","sci_sym_get_str_param";
		"sym_setObjCoeff","sci_sym_setObjCoeff";
		"sym_setObjSense","sci_sym_setObjSense";
		"sym_setVarLower","sci_sym_setVarBound";
		"sym_setVarUpper","sci_sym_setVarBound";
		"sym_setConstrLower","sci_sym_setConstrBound";
		"sym_setConstrUpper","sci_sym_setConstrBound";
		"sym_setConstrType","sci_sym_setConstrType";
		"sym_set_continuous","sci_sym_set_continuous";
		"sym_set_integer","sci_sym_set_integer";
		"sym_getMatrix","sci_sym_get_matrix";
		"sym_getConstrSense","sci_sym_get_row_sense";
		"sym_addConstr","sci_sym_addConstr";
		"sym_addVar","sci_sym_addVar";
		"sym_getIterCount","sci_sym_get_iteration_count";
		"sym_get_matrix","sci_sym_get_matrix";
		"sym_getPrimalBound","sci_sym_getPrimalBound";
		"sym_setPrimalBound","sci_sym_setPrimalBound";
		"sym_setVarSoln","sci_sym_setColSoln";
		"sym_getConstrActivity","sci_sym_getRowActivity";
		"sym_getObjSense","sci_sym_getObjSense";
		"sym_delete_cols","sci_sym_delete_cols";
		"sym_delete_rows","sci_sym_delete_rows";
	], ..
	[
		"globals.cpp",
		"sci_iofunc.hpp",
		"sci_iofunc.cpp",
		"sci_sym_openclose.cpp",
		"sci_solver_status_query_functions.cpp",
		"sci_sym_solve.cpp",
		"sci_sym_loadproblem.cpp",
		"sci_sym_isenvactive.cpp",
		"sci_sym_load_mps.cpp",
		"sci_vartype.cpp",
		"sci_sym_getinfinity.cpp",
		"sci_sym_solution.cpp",
		"sym_data_query_functions.cpp"
		"sci_sym_set_variables.cpp",
		"sci_sym_setobj.cpp",
		"sci_sym_varbounds.cpp",
		"sci_sym_rowmod.cpp",
		"sci_sym_set_indices.cpp",
		"sci_sym_addrowcol.cpp",
		"sci_sym_primalbound.cpp",
		"sci_sym_setcolsoln.cpp",
		"sci_sym_getrowact.cpp",
		"sci_sym_getobjsense.cpp",
		"sci_sym_remove.cpp",
	], ..
	get_absolute_file_path("builder.sce"), [], ["-lSym"], ["-w -fpermissive -I/usr/include/coin"], [], "g++");

clear WITHOUT_AUTO_PUTLHSVAR;

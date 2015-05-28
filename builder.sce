mode(-1)
lines(0)

//Symphony toolbox builder
//By Keyur Joshi, Sai Kiran, and Iswarya

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
		"sym_isOptimal","sci_sym_is_proven_optimal";
		"sym_isInfeasible","sci_sym_is_proven_primal_infeasible";
		"sym_isAbandoned","sci_sym_is_abandoned";
		"sym_isIterLimitReached","sci_sym_is_iteration_limit_reached";
		"sym_isTimeLimitReached","sci_sym_is_time_limit_reached";
		"sym_isTargetGapAchieved","sci_sym_is_target_gap_achieved";
		"sym_isContinuous","sci_sym_isContinuous";
		"sym_isBinary","sci_sym_isBinary";
		"sym_isInteger","sci_sym_isInteger";
		"sym_getInfinity","sci_sym_getInfinity";
		"sym_getVarSoln","sci_sym_getVarSoln";
		"sym_getObjVal","sci_sym_getObjVal";
		"sym_getNumRows","sci_sym_get_num_int";
		"sym_getNumCols","sci_sym_get_num_int";
		"sym_getNumElements","sci_sym_get_num_int";
		"sym_getColLower","sci_sym_get_dbl_arr";
		"sym_getColUpper","sci_sym_get_dbl_arr";
		"sym_getRhs","sci_sym_get_dbl_arr";
		"sym_getRowRange","sci_sym_get_dbl_arr";
		"sym_getRowLower","sci_sym_get_dbl_arr";
		"sym_getRowUpper","sci_sym_get_dbl_arr";
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
	], ..
	[
		"globals.cpp",
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
	], ..
	get_absolute_file_path("builder.sce"), [], ["-lSym"], ["-fpermissive -I/usr/include/coin"], [], "g++");

clear WITHOUT_AUTO_PUTLHSVAR;

//Symphony toolbox builder
//By Keyur Joshi and Sai Kiran
//Last edit on 22-5-15
mode(-1)
lines(0)

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
	], ..
	get_absolute_file_path("builder.sce"), [], ..
	["-fopenmp -lSym -lCgl -lOsiClp -lClp -lOsi -lCoinUtils -lbz2 -lz -llapack -lblas -lm"], ..
	["-fpermissive -w -DSYMPHONY_BUILD -I/usr/include/coin"], ..
	[], "g++");

clear WITHOUT_AUTO_PUTLHSVAR;

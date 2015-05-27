mode(-1); //run silently, only displaying what is needed

//Symphony Toolbox
//Interactive script for loading a basic MIP problem to Symphony
//Useful for beginners/casual users
//Made by Keyur Joshi
//Last edit on 21-5-15

//only run if environment has been set up already
if(sym_isEnvActive()==0) then
	//show welcome message
	mprintf("\nMixed integer linear programming using Symphony library\nPlease note that this interactive script only supports simple problems\n\n")

	//ask for data, with complete foolproofing
	mprintf("Enter number of variables:");
	while %t
		sym_numVars=input('');
		if(typeof(sym_numVars)=="constant") if(isreal(sym_numVars)) if(size(sym_numVars)==[1,1]) if(int(sym_numVars)==sym_numVars) if(sym_numVars>0)
			break;
		end end end end end
		mprintf("Please enter a natrual number.");
	end

	mprintf("Enter number of constraints:");
	while %t
		sym_numConstr=input('');
		if(typeof(sym_numConstr)=="constant") if(isreal(sym_numConstr)) if(size(sym_numConstr)==[1,1]) if(int(sym_numConstr)==sym_numConstr) if(sym_numConstr>=0)
			break;
		end end end end end
		mprintf("Please enter a nonnegative integer.");
	end

	mprintf("Enter 1 by %d matrix representing the lower bounds of the variables:",sym_numVars);
	while %t
		sym_lowerBounds=input('');
		if(typeof(sym_lowerBounds)=="constant") if(isreal(sym_lowerBounds)) if(size(sym_lowerBounds)==[1,sym_numVars])
			break;
		end end end
		mprintf("Please enter a 1 by %d matrix of real numbers.",sym_numVars);
	end

	mprintf("Enter 1 by %d matrix representing the upper bounds of the variables:",sym_numVars);
	while %t
		sym_upperBounds=input('');
		if(typeof(sym_upperBounds)=="constant") if(isreal(sym_upperBounds)) if(size(sym_upperBounds)==[1,sym_numVars])
			break;
		end end end
		mprintf("Please enter a 1 by %d matrix of real numbers.",sym_numVars);
	end

	mprintf("Enter 1 by %d matrix representing the coefficients\nof the variables in the objective function:",sym_numVars);
	while %t
		sym_objective=input('');
		if(typeof(sym_objective)=="constant") if(isreal(sym_objective)) if(size(sym_objective)==[1,sym_numVars])
			break;
		end end end
		mprintf("Please enter a 1 by %d matrix of real numbers.",sym_numVars);
	end
	mprintf("Do you want to minimize the objective (enter 1)\nor maximize the objective (enter 2):");
	while %t
		sym_objType=input('');
		if(sym_objType==1 | sym_objType==2)
			break;
		end
		mprintf("Please enter 1 or 2.");
	end
	//symphony only minimizes objectives, so convert maxmimization problems to minimization problems
	if(sym_objType==2) then
		for sym_iter=1:sym_numVars
			sym_objective(1,sym_iter) = -sym_objective(1,sym_iter);
		end
	end

	mprintf("Enter 1 by %d matrix of booleans representing wether\nthe variables are constrained to be integers:",sym_numVars);
	while %t
		sym_isIntVar=input('');
		if(typeof(sym_isIntVar)=="boolean") if(size(sym_isIntVar)==[1,sym_numVars])
			break;
		end end
		mprintf("Please enter a 1 by %d matrix of booleans.",sym_numVars);
	end

	//initialize some matrices to empty
	sym_conVals=[];
	sym_conType=[];
	sym_conRHS=[];
	for sym_iter=1:sym_numConstr
		mprintf("Enter 1 by %d matrix representing the coefficients\nof the variables in constraint no. %d:",sym_numVars,sym_iter);
		while %t
			sym_input=input('');
			if(typeof(sym_input)=="constant") if(isreal(sym_input)) if(size(sym_input)==[1,sym_numVars])
				break;
			end end end
			mprintf("Please enter a 1 by %d matrix of real numbers.",sym_numVars);
		end
		sym_conVals=[sym_conVals;sym_input];
		mprintf("Enter type of constraint: Less than (enter 1),\nEqual to (enter 2), or Greater than (enter 3):");
		while %t
			sym_input=input('');
			if(sym_input==1 | sym_input==2 | sym_input==3)
				break;
			end
			mprintf("Please enter 1,2, or 3.");
		end
		if(sym_input==1) then
			sym_input="L";
		elseif(sym_input==2) then
			sym_input="E";
		elseif(sym_input==3) then
			sym_input="G";
		end
		sym_conType=[sym_conType;sym_input];
		mprintf("Enter RHS of constraint no. %d:",sym_iter);
		while %t
			sym_input=input('');
			if(typeof(sym_input)=="constant") if(isreal(sym_input)) if(size(sym_input)==[1,1])
				break;
			end end end
			mprintf("Please enter a real number.");
		end
		sym_conRHS=[sym_conRHS;sym_input];
	end

	//load problem into symphony environment
	sym_loadProblemBasic(sym_numVars,sym_numConstr,sym_lowerBounds,sym_upperBounds, ..
		sym_objective,sym_isIntVar,sym_conVals,sym_conType,sym_conRHS);

	//cleanup of temp variables
	clear sym_numVars sym_numConstr sym_lowerBounds sym_upperBounds sym_objective sym_input sym_objType sym_isIntVar sym_conVals sym_conType sym_conRHS sym_iter
end

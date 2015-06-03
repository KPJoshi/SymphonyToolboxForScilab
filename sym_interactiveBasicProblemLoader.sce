mode(-1); //run silently, only displaying what is needed

//Symphony Toolbox
//Interactive script for loading a MIP problem to Symphony
//Made by Keyur Joshi

//only run if environment has been set up already
if(sym_isEnvActive()) then
	//show welcome message
	mprintf("\nMixed integer linear programming using Symphony library\n\n")

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
	mprintf("Do you want to minimize the objective (enter 1)\nor maximize the objective (enter -1):");
	while %t
		sym_objSense=input('');
		if(sym_objSense==1 | sym_objSense==-1)
			break;
		end
		mprintf("Please enter 1 or -1.");
	end

	mprintf("Enter 1 by %d matrix of booleans representing wether\nthe variables are constrained to be integers:",sym_numVars);
	while %t
		sym_isIntVar=input('');
		if(typeof(sym_isIntVar)=="boolean") if(size(sym_isIntVar)==[1,sym_numVars])
			break;
		end end
		mprintf("Please enter a 1 by %d matrix of booleans.",sym_numVars);
	end

	mprintf("Enter %d by %d SPARSE matrix of doubles representing\nthe coefficients of the variables in the constraints:",sym_numConstr,sym_numVars);
	while %t
		sym_conMatrix=input('');
		if(typeof(sym_conMatrix)=="sparse") if(size(sym_conMatrix)==[sym_numConstr,sym_numVars])
			break;
		end end
		mprintf("Please enter a %d by %d SPARSE matrix of doubles.",sym_numConstr,sym_numVars);
	end
	
	mprintf("Enter %d by 1 matrix of doubles representing\nthe lower bounds of the constraints:",sym_numConstr);
	while %t
		sym_conLower=input('');
		if(typeof(sym_conLower)=="constant") if(size(sym_conLower)==[sym_numConstr,1])
			break;
		end end
		mprintf("Please enter a %d by 1 matrix of doubles.",sym_numConstr);
	end
	
	mprintf("Enter %d by 1 matrix of doubles representing\nthe upper bounds of the constraints:",sym_numConstr);
	while %t
		sym_conUpper=input('');
		if(typeof(sym_conUpper)=="constant") if(size(sym_conUpper)==[sym_numConstr,1])
			break;
		end end
		mprintf("Please enter a %d by 1 matrix of doubles.",sym_numConstr);
	end
	
	//load the problem
	sym_loadProblem(sym_numVars,sym_numConstr,sym_lowerBounds,sym_upperBounds,sym_objective,sym_isIntVar,sym_objSense,sym_conMatrix,sym_conLower,sym_conUpper);

	//clear temp variables
	clear sym_numVars sym_numConstr sym_lowerBounds sym_upperBounds sym_objective sym_isIntVar sym_objSense sym_conMatrix sym_conLower sym_conUpper;
end

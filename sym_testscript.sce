//Symphony Toolbox
//Script to test the toolbox
//Made by Keyur Joshi

//--------------
//initialization
//--------------

exec loader.sce

function performLotsOfTests(numVar)
	//be verbose
	mode(1)
	//get data
	sym_getNumVar
	sym_getNumConstr
	sym_getVarLower
	sym_getVarUpper
	sym_getObjCoeff
	sym_getObjSense
	for iter=0:(numVar-1)
		sym_isContinuous(iter)
		sym_isBinary(iter)
		sym_isInteger(iter)
	end
	sym_getNumElements
	sym_get_matrix
	sym_getConstrLower
	sym_getConstrUpper
	sym_getConstrRange
	sym_getConstrSense
	//solve the problem
	sym_solve
	//get more data
	sym_getStatus
	sym_isOptimal
	sym_isInfeasible
	sym_isAbandoned
	sym_isIterLimitReached
	sym_getIterCount
	sym_isTimeLimitReached
	sym_isTargetGapAchieved
	sym_getVarSoln
	sym_getObjVal
	sym_getPrimalBound
	sym_getConstrActivity
endfunction

//open environment
sym_open

//check that it is open
sym_isEnvActive

//misc. checks
sym_getInfinity

//---------------------------------------
//test 1: problem loader and data viewers
//---------------------------------------

//test 1 problem 1 : integer problem

//load the problem
sym_loadProblem(2,2,[0,0],[%inf,%inf],[1,1],[%t,%t],sym_maximize,sparse([1,2;2,1]),[-%inf;-%inf],[7;6.5])

performLotsOfTests(2)

//test 1 problem 2 : pure non-integer problem

//load the problem
sym_loadProblemBasic(2,2,[0,0],[%inf,%inf],[-1,-1],[%f,%f],sym_minimize,[1,2;2,1],[-%inf;-%inf],[7;6.5])

performLotsOfTests(2)

//test 1 problem 3 : infeasible problem

//load the problem
sym_loadProblem(2,1,[0.1,0.1],[0.9,0.9],[1,1],[%f,%t],sym_maximize,sparse([1,1]),[-%inf],[1])

performLotsOfTests(2)

//------------
//finalization
//------------

//close environment
sym_close

//check that it has closed
sym_isEnvActive
